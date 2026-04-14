// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from smarthome_vision:msg/DetectedTarget.idl
// generated code does not contain a copyright notice

#ifndef SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "smarthome_vision/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "smarthome_vision/msg/detail/detected_target__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace smarthome_vision
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_smarthome_vision
cdr_serialize(
  const smarthome_vision::msg::DetectedTarget & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_smarthome_vision
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  smarthome_vision::msg::DetectedTarget & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_smarthome_vision
get_serialized_size(
  const smarthome_vision::msg::DetectedTarget & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_smarthome_vision
max_serialized_size_DetectedTarget(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace smarthome_vision

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_smarthome_vision
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, smarthome_vision, msg, DetectedTarget)();

#ifdef __cplusplus
}
#endif

#endif  // SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
