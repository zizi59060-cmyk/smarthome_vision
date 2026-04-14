#pragma once

#include <cstdint>

namespace smarthome_vision
{

struct __attribute__((packed)) VisionToGimbal
{
  uint8_t head[2] = {'S', 'P'};
  uint8_t tracking = 0;
  uint8_t class_id = 0;
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  uint16_t crc16 = 0;
};

}  // namespace smarthome_vision