#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

#include "smarthome_vision/protocol.hpp"

namespace smarthome_vision
{

class GimbalBridge
{
public:
  GimbalBridge(const std::string & device, int baudrate, int reconnect_interval_ms = 1000);
  ~GimbalBridge();

  bool isOpened() const;

  bool sendTarget(uint8_t mode, bool tracking, uint8_t class_id, float x, float y, float z);
  bool updateReceive();

  uint8_t getMode() const;

  // 构造将要发给下位机的十六进制字符串，用于 ROS topic 调试输出。
  std::string buildTargetPacketHex(
    uint8_t mode, bool tracking, uint8_t class_id, float x, float y, float z) const;

  // 立即尝试重连一次；通常不需要外部调用，sendTarget/updateReceive 会自动触发。
  bool reconnectNow();

  // 设置自动重连间隔，单位 ms；设置为 0 表示每次读写前都允许尝试重连。
  void setReconnectIntervalMs(int reconnect_interval_ms);

private:
  bool openPort();
  void closePort();
  bool ensurePortOpen();
  bool shouldTryReconnect() const;
  void markDisconnected(const char * reason);
  bool parseModePacket();

  std::string device_;
  int baudrate_ = 115200;
  int fd_ = -1;

  std::vector<uint8_t> rx_buffer_;
  uint8_t current_mode_ = static_cast<uint8_t>(VisionMode::IDLE);

  std::chrono::milliseconds reconnect_interval_{1000};
  std::chrono::steady_clock::time_point last_reconnect_attempt_{
    std::chrono::steady_clock::time_point::min()};
};

}  // namespace smarthome_vision