// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from smarthome_vision:msg/DetectedTarget.idl
// generated code does not contain a copyright notice

#ifndef SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__STRUCT_H_
#define SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'corners_uv'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/DetectedTarget in the package smarthome_vision.
typedef struct smarthome_vision__msg__DetectedTarget
{
  builtin_interfaces__msg__Time stamp;
  uint8_t mode;
  bool tracking;
  int32_t class_id;
  float score;
  float x;
  float y;
  float z;
  rosidl_runtime_c__float__Sequence corners_uv;
} smarthome_vision__msg__DetectedTarget;

// Struct for a sequence of smarthome_vision__msg__DetectedTarget.
typedef struct smarthome_vision__msg__DetectedTarget__Sequence
{
  smarthome_vision__msg__DetectedTarget * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} smarthome_vision__msg__DetectedTarget__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__STRUCT_H_
