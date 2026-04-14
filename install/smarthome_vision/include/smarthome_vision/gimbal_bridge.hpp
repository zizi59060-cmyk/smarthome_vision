#pragma once

#include <string>

namespace smarthome_vision
{

class GimbalBridge
{
public:
  GimbalBridge(const std::string & device, int baudrate);
  ~GimbalBridge();

  bool isOpened() const;
  bool sendTarget(bool tracking, uint8_t class_id, float x, float y, float z);

private:
  bool openPort();
  void closePort();

private:
  int fd_ = -1;
  std::string device_;
  int baudrate_ = 115200;
};

}  // namespace smarthome_vision