#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "smarthome_vision/protocol.hpp"

namespace smarthome_vision
{

class GimbalBridge
{
public:
  GimbalBridge(const std::string & device, int baudrate);
  ~GimbalBridge();

  bool isOpened() const;

  // 发送视觉结果
  bool sendTarget(uint8_t mode, bool tracking, uint8_t class_id, float x, float y, float z);

  // 读取串口，刷新最新 mode
  bool updateReceive();

  // 获取最新 mode
  uint8_t getMode() const;

private:
  bool openPort();
  void closePort();

  // 从接收缓冲区解析最新合法包
  bool parseModePacket();

private:
  int fd_ = -1;
  std::string device_;
  int baudrate_ = 115200;

  uint8_t current_mode_ = static_cast<uint8_t>(VisionMode::IDLE);
  std::vector<uint8_t> rx_buffer_;
};

}  // namespace smarthome_vision