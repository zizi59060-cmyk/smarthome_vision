#include "smarthome_vision/gimbal_bridge.hpp"

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "smarthome_vision/crc16.hpp"
#include "smarthome_vision/protocol.hpp"

namespace smarthome_vision
{
namespace
{

speed_t toSpeed(int baudrate)
{
  switch (baudrate) {
    case 9600: return B9600;
    case 19200: return B19200;
    case 38400: return B38400;
    case 57600: return B57600;
    case 115200: return B115200;
#ifdef B230400
    case 230400: return B230400;
#endif
#ifdef B460800
    case 460800: return B460800;
#endif
#ifdef B921600
    case 921600: return B921600;
#endif
    default:
      std::cerr << "[GimbalBridge] unsupported baudrate " << baudrate
                << ", fallback to 115200" << std::endl;
      return B115200;
  }
}

bool isTemporaryIoError(int err)
{
  return err == EINTR || err == EAGAIN || err == EWOULDBLOCK;
}

}  // namespace

GimbalBridge::GimbalBridge(
  const std::string & device, int baudrate, int reconnect_interval_ms)
: device_(device),
  baudrate_(baudrate),
  reconnect_interval_(std::chrono::milliseconds(std::max(0, reconnect_interval_ms)))
{
  reconnectNow();
}

GimbalBridge::~GimbalBridge()
{
  closePort();
}

bool GimbalBridge::isOpened() const
{
  return fd_ >= 0;
}

void GimbalBridge::setReconnectIntervalMs(int reconnect_interval_ms)
{
  reconnect_interval_ = std::chrono::milliseconds(std::max(0, reconnect_interval_ms));
}

bool GimbalBridge::shouldTryReconnect() const
{
  if (isOpened()) {
    return false;
  }

  if (last_reconnect_attempt_ == std::chrono::steady_clock::time_point::min()) {
    return true;
  }

  const auto now = std::chrono::steady_clock::now();
  return now - last_reconnect_attempt_ >= reconnect_interval_;
}

bool GimbalBridge::ensurePortOpen()
{
  if (isOpened()) {
    return true;
  }

  if (!shouldTryReconnect()) {
    return false;
  }

  return reconnectNow();
}

bool GimbalBridge::reconnectNow()
{
  closePort();
  last_reconnect_attempt_ = std::chrono::steady_clock::now();
  return openPort();
}

bool GimbalBridge::openPort()
{
  if (isOpened()) {
    return true;
  }

  fd_ = open(device_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if (fd_ < 0) {
    std::cerr << "[GimbalBridge] failed to open " << device_
              << ": " << std::strerror(errno) << std::endl;
    return false;
  }

  termios tty;
  std::memset(&tty, 0, sizeof(tty));

  if (tcgetattr(fd_, &tty) != 0) {
    std::cerr << "[GimbalBridge] tcgetattr failed on " << device_
              << ": " << std::strerror(errno) << std::endl;
    closePort();
    return false;
  }

  cfsetospeed(&tty, toSpeed(baudrate_));
  cfsetispeed(&tty, toSpeed(baudrate_));

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
  tty.c_iflag &= ~IGNBRK;
  tty.c_lflag = 0;
  tty.c_oflag = 0;

  // read() 最多阻塞 0.1 s，保持原工程的串口读取行为。
  tty.c_cc[VMIN] = 0;
  tty.c_cc[VTIME] = 1;

  tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  tty.c_cflag |= (CLOCAL | CREAD);
  tty.c_cflag &= ~(PARENB | PARODD);
  tty.c_cflag &= ~CSTOPB;
#ifdef CRTSCTS
  tty.c_cflag &= ~CRTSCTS;
#endif

  if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
    std::cerr << "[GimbalBridge] tcsetattr failed on " << device_
              << ": " << std::strerror(errno) << std::endl;
    closePort();
    return false;
  }

  tcflush(fd_, TCIOFLUSH);

  std::cerr << "[GimbalBridge] opened " << device_
            << " @ " << baudrate_ << std::endl;
  return true;
}

void GimbalBridge::closePort()
{
  if (fd_ >= 0) {
    const int old_fd = fd_;
    fd_ = -1;
    close(old_fd);
  }
  rx_buffer_.clear();
}

void GimbalBridge::markDisconnected(const char * reason)
{
  if (reason != nullptr) {
    std::cerr << "[GimbalBridge] " << reason
              << ", close port and wait reconnect: " << device_ << std::endl;
  }
  closePort();
}

std::string GimbalBridge::buildTargetPacketHex(
  uint8_t mode, bool tracking, uint8_t class_id, float x, float y, float z) const
{
  VisionToGimbal packet;
  packet.mode = mode;
  packet.tracking = tracking ? 1 : 0;
  packet.class_id = class_id;
  packet.x = x;
  packet.y = y;
  packet.z = z;
  packet.crc16 = crc16_modbus(
    reinterpret_cast<const uint8_t *>(&packet),
    static_cast<uint32_t>(sizeof(packet) - sizeof(packet.crc16)));

  const uint8_t * bytes = reinterpret_cast<const uint8_t *>(&packet);

  std::ostringstream oss;
  oss << std::uppercase << std::hex << std::setfill('0');
  for (size_t i = 0; i < sizeof(packet); ++i) {
    oss << std::setw(2) << static_cast<int>(bytes[i]);
    if (i + 1 < sizeof(packet)) {
      oss << " ";
    }
  }

  return oss.str();
}

bool GimbalBridge::sendTarget(
  uint8_t mode, bool tracking, uint8_t class_id, float x, float y, float z)
{
  if (!ensurePortOpen()) {
    return false;
  }

  VisionToGimbal packet;
  packet.mode = mode;
  packet.tracking = tracking ? 1 : 0;
  packet.class_id = class_id;
  packet.x = x;
  packet.y = y;
  packet.z = z;
  packet.crc16 = crc16_modbus(
    reinterpret_cast<const uint8_t *>(&packet),
    static_cast<uint32_t>(sizeof(packet) - sizeof(packet.crc16)));

  const uint8_t * data = reinterpret_cast<const uint8_t *>(&packet);
  size_t total_written = 0;

  while (total_written < sizeof(packet)) {
    const ssize_t n = write(fd_, data + total_written, sizeof(packet) - total_written);

    if (n > 0) {
      total_written += static_cast<size_t>(n);
      continue;
    }

    if (n < 0 && errno == EINTR) {
      continue;
    }

    if (n < 0 && isTemporaryIoError(errno)) {
      return false;
    }

    if (n < 0) {
      std::cerr << "[GimbalBridge] write failed on " << device_
                << ": " << std::strerror(errno) << std::endl;
    } else {
      std::cerr << "[GimbalBridge] write returned 0 on " << device_ << std::endl;
    }

    markDisconnected("serial write disconnected or invalid");
    return false;
  }

  return true;
}

bool GimbalBridge::updateReceive()
{
  if (!ensurePortOpen()) {
    return false;
  }

  uint8_t temp[64];
  const ssize_t n = read(fd_, temp, sizeof(temp));

  if (n < 0) {
    if (isTemporaryIoError(errno)) {
      return false;
    }

    std::cerr << "[GimbalBridge] read failed on " << device_
              << ": " << std::strerror(errno) << std::endl;
    markDisconnected("serial read disconnected or invalid");
    return false;
  }

  // VMIN=0/VTIME=1 时，没有收到数据会返回 0，这不是断线。
  if (n == 0) {
    return false;
  }

  rx_buffer_.insert(rx_buffer_.end(), temp, temp + n);

  if (rx_buffer_.size() > 1024) {
    rx_buffer_.erase(rx_buffer_.begin(), rx_buffer_.end() - 1024);
  }

  return parseModePacket();
}

bool GimbalBridge::parseModePacket()
{
  const size_t packet_size = sizeof(GimbalToVision);

  while (rx_buffer_.size() >= packet_size) {
    size_t head_pos = rx_buffer_.size();

    for (size_t i = 0; i + 1 < rx_buffer_.size(); ++i) {
      if (rx_buffer_[i] == 'V' && rx_buffer_[i + 1] == 'S') {
        head_pos = i;
        break;
      }
    }

    if (head_pos == rx_buffer_.size()) {
      rx_buffer_.clear();
      return false;
    }

    if (head_pos > 0) {
      rx_buffer_.erase(rx_buffer_.begin(), rx_buffer_.begin() + head_pos);
    }

    if (rx_buffer_.size() < packet_size) {
      return false;
    }

    GimbalToVision packet;
    std::memcpy(&packet, rx_buffer_.data(), packet_size);

    const uint16_t calc_crc = crc16_modbus(
      reinterpret_cast<const uint8_t *>(&packet),
      static_cast<uint32_t>(packet_size - sizeof(packet.crc16)));

    if (calc_crc == packet.crc16) {
      current_mode_ = packet.mode;
      rx_buffer_.erase(rx_buffer_.begin(), rx_buffer_.begin() + packet_size);
      return true;
    }

    rx_buffer_.erase(rx_buffer_.begin());
  }

  return false;
}

uint8_t GimbalBridge::getMode() const
{
  return current_mode_;
}

}  // namespace smarthome_vision