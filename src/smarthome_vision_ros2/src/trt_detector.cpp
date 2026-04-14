#include "smarthome_vision/trt_detector.hpp"

#include <cuda_runtime.h>
#include <NvInfer.h>

#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/imgproc.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath> // 引入 cmath 以使用 std::exp

namespace smarthome_vision
{

namespace
{

class TRTLogger : public nvinfer1::ILogger
{
public:
  void log(Severity severity, const char * msg) noexcept override
  {
    if (severity <= Severity::kWARNING) {
      std::cerr << "[TensorRT] " << msg << std::endl;
    }
  }
};

TRTLogger g_logger;

inline size_t getSizeByDim(const nvinfer1::Dims & dims)
{
  size_t size = 1;
  for (int i = 0; i < dims.nbDims; ++i) {
    size *= static_cast<size_t>(dims.d[i]);
  }
  return size;
}

inline void checkCuda(cudaError_t code, const std::string & msg)
{
  if (code != cudaSuccess) {
    throw std::runtime_error(msg + ": " + cudaGetErrorString(code));
  }
}

}  // namespace

TRTDetector::TRTDetector(
  const std::string & engine_path,
  int input_width,
  int input_height,
  float conf_thres,
  float score_thres,
  bool output_keypoints,
  bool use_cuda_preprocess)
: engine_path_(engine_path),
  input_width_(input_width),
  input_height_(input_height),
  conf_thres_(conf_thres),
  score_thres_(score_thres),
  output_keypoints_(output_keypoints),
  use_cuda_preprocess_(use_cuda_preprocess)
{
  if (engine_path_.empty()) {
    throw std::runtime_error("engine path is empty");
  }

  auto engine_data = loadEngineFile(engine_path_);

  runtime_ = nvinfer1::createInferRuntime(g_logger);
  if (!runtime_) {
    throw std::runtime_error("failed to create TensorRT runtime");
  }

  engine_ = runtime_->deserializeCudaEngine(engine_data.data(), engine_data.size());
  if (!engine_) {
    throw std::runtime_error("failed to deserialize engine: " + engine_path_);
  }

  context_ = engine_->createExecutionContext();
  if (!context_) {
    throw std::runtime_error("failed to create execution context");
  }

  const int nb = engine_->getNbIOTensors();
  for (int i = 0; i < nb; ++i) {
    const char * name = engine_->getIOTensorName(i);
    auto mode = engine_->getTensorIOMode(name);
    if (mode == nvinfer1::TensorIOMode::kINPUT) {
      input_name_ = name;
    } else if (mode == nvinfer1::TensorIOMode::kOUTPUT) {
      output_name_ = name;
    }
  }

  if (input_name_.empty() || output_name_.empty()) {
    throw std::runtime_error("failed to find input/output tensor names");
  }

  auto input_dims = engine_->getTensorShape(input_name_.c_str());
  bool dynamic_input = false;
  for (int i = 0; i < input_dims.nbDims; ++i) {
    if (input_dims.d[i] == -1) {
      dynamic_input = true;
      break;
    }
  }

  if (dynamic_input) {
    nvinfer1::Dims4 fixed_dims{1, 3, input_height_, input_width_};
    if (!context_->setInputShape(input_name_.c_str(), fixed_dims)) {
      throw std::runtime_error("failed to set dynamic input shape");
    }
    input_dims = context_->getTensorShape(input_name_.c_str());
  }

  auto output_dims = context_->getTensorShape(output_name_.c_str());

  // 初始化时打印一次模型输出维度，确认加载正常
  std::cout << "\n========== 模型加载成功 ==========\n";
  std::cout << "Engine Path: " << engine_path_ << "\n";
  std::cout << "Output Shape: [ ";
  for (int i = 0; i < output_dims.nbDims; ++i) {
    std::cout << output_dims.d[i] << (i == output_dims.nbDims - 1 ? "" : ", ");
  }
  std::cout << " ]\n===================================\n\n";

  input_numel_ = getSizeByDim(input_dims);
  output_numel_ = getSizeByDim(output_dims);
  host_output_.resize(output_numel_);

  checkCuda(cudaStreamCreate(&stream_), "cudaStreamCreate failed");
  checkCuda(cudaMalloc(&device_buffers_[0], input_numel_ * sizeof(float)), "cudaMalloc input failed");
  checkCuda(cudaMalloc(&device_buffers_[1], output_numel_ * sizeof(float)), "cudaMalloc output failed");

  if (!context_->setTensorAddress(input_name_.c_str(), device_buffers_[0])) {
    throw std::runtime_error("failed to set input tensor address");
  }
  if (!context_->setTensorAddress(output_name_.c_str(), device_buffers_[1])) {
    throw std::runtime_error("failed to set output tensor address");
  }
}

TRTDetector::~TRTDetector()
{
  if (device_buffers_[0]) cudaFree(device_buffers_[0]);
  if (device_buffers_[1]) cudaFree(device_buffers_[1]);
  if (stream_) cudaStreamDestroy(stream_);
  if (context_) delete context_;
  if (engine_) delete engine_;
  if (runtime_) delete runtime_;
}

std::vector<char> TRTDetector::loadEngineFile(const std::string & path)
{
  std::ifstream file(path, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("failed to open engine file: " + path);
  }

  file.seekg(0, std::ios::end);
  const size_t size = static_cast<size_t>(file.tellg());
  file.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  file.read(buffer.data(), static_cast<std::streamsize>(size));
  return buffer;
}

void TRTDetector::preprocess(
  const cv::Mat & image,
  std::vector<float> & input_tensor,
  float & scale_x,
  float & scale_y) const
{
  scale_x = static_cast<float>(image.cols) / static_cast<float>(input_width_);
  scale_y = static_cast<float>(image.rows) / static_cast<float>(input_height_);

  cv::Mat rgb_float;

  if (use_cuda_preprocess_) {
    cv::cuda::GpuMat gpu_bgr, gpu_resized, gpu_rgb;
    gpu_bgr.upload(image);
    cv::cuda::resize(gpu_bgr, gpu_resized, cv::Size(input_width_, input_height_));
    cv::cuda::cvtColor(gpu_resized, gpu_rgb, cv::COLOR_BGR2RGB);
    cv::Mat rgb;
    gpu_rgb.download(rgb);
    rgb.convertTo(rgb_float, CV_32F, 1.0 / 255.0);
  } else {
    cv::Mat resized, rgb;
    cv::resize(image, resized, cv::Size(input_width_, input_height_));
    cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);
    rgb.convertTo(rgb_float, CV_32F, 1.0 / 255.0);
  }

  input_tensor.resize(input_numel_);
  const int hw = input_width_ * input_height_;

  std::vector<cv::Mat> chw(3);
  for (int c = 0; c < 3; ++c) {
    chw[c] = cv::Mat(input_height_, input_width_, CV_32F, input_tensor.data() + c * hw);
  }
  cv::split(rgb_float, chw);
}

std::vector<RawPrediction> TRTDetector::infer(const cv::Mat & image)
{
  std::vector<RawPrediction> results;
  if (image.empty()) {
    return results;
  }

  float scale_x = 1.0f;
  float scale_y = 1.0f;
  std::vector<float> input_tensor;
  preprocess(image, input_tensor, scale_x, scale_y);

  checkCuda(
    cudaMemcpyAsync(
      device_buffers_[0],
      input_tensor.data(),
      input_numel_ * sizeof(float),
      cudaMemcpyHostToDevice,
      stream_),
    "cudaMemcpyAsync input failed");

  if (!context_->enqueueV3(stream_)) {
    throw std::runtime_error("TensorRT enqueueV3 failed");
  }

  checkCuda(
    cudaMemcpyAsync(
      host_output_.data(),
      device_buffers_[1],
      output_numel_ * sizeof(float),
      cudaMemcpyDeviceToHost,
      stream_),
    "cudaMemcpyAsync output failed");

  checkCuda(cudaStreamSynchronize(stream_), "cudaStreamSynchronize failed");

  // 【核心修改1】设定正确的步长为 18
  const int stride = 18;
  const int num_preds = static_cast<int>(output_numel_ / stride);

  return decode(host_output_.data(), num_preds, 0, scale_x, scale_y, image.cols, image.rows);
}

std::vector<RawPrediction> TRTDetector::decode(
  const float * output,
  int num_preds,
  int reserved,
  float scale_x,
  float scale_y,
  int image_w,
  int image_h) const
{
  (void)reserved;

  std::vector<RawPrediction> results;
  if (!output || num_preds <= 0) {
    return results;
  }

  // 【核心修改2】设定正确的步长为 18
  const int stride = 18;

  for (int i = 0; i < num_preds; ++i) {
    const float * row = output + i * stride;

    // --- 核心修复：引入 Sigmoid 计算真实概率 ---
    const float raw_score = row[4];
    const float score = 1.0f / (1.0f + std::exp(-raw_score));
    
    // 如果转换后的真实概率低于阈值，则跳过
    if (score < score_thres_) {
      continue;
    }
    // ------------------------------------------

    RawPrediction pred;
    pred.score = score;
    // 第 5 列是类别 ID
    pred.class_id = static_cast<int>(row[5]);

    // 读取包围框 cx, cy, w, h
    const float cx = row[0] * scale_x;
    const float cy = row[1] * scale_y;
    const float w  = row[2] * scale_x;
    const float h  = row[3] * scale_y;

    float x1 = cx - 0.5f * w;
    float y1 = cy - 0.5f * h;
    float x2 = cx + 0.5f * w;
    float y2 = cy + 0.5f * h;

    // 限制在图像边界内
    x1 = std::max(0.0f, std::min(x1, static_cast<float>(image_w - 1)));
    y1 = std::max(0.0f, std::min(y1, static_cast<float>(image_h - 1)));
    x2 = std::max(0.0f, std::min(x2, static_cast<float>(image_w - 1)));
    y2 = std::max(0.0f, std::min(y2, static_cast<float>(image_h - 1)));

    pred.bbox = cv::Rect2f(x1, y1, std::max(0.0f, x2 - x1), std::max(0.0f, y2 - y1));

    // 解析四个关键点 (跳过中间的置信度列)
    if (output_keypoints_) {
      pred.has_keypoints = true;
      pred.keypoints[0] = cv::Point2f(row[6]  * scale_x, row[7]  * scale_y);
      pred.keypoints[1] = cv::Point2f(row[9]  * scale_x, row[10] * scale_y);
      pred.keypoints[2] = cv::Point2f(row[12] * scale_x, row[13] * scale_y);
      pred.keypoints[3] = cv::Point2f(row[15] * scale_x, row[16] * scale_y);
    } else {
      pred.has_keypoints = false;
    }

    results.push_back(pred);
  }

  return results;
}

}  // namespace smarthome_vision