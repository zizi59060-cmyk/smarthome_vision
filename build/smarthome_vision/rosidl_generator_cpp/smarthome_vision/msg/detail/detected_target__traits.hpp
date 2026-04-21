// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from smarthome_vision:msg/DetectedTarget.idl
// generated code does not contain a copyright notice

#ifndef SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__TRAITS_HPP_
#define SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "smarthome_vision/msg/detail/detected_target__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace smarthome_vision
{

namespace msg
{

inline void to_flow_style_yaml(
  const DetectedTarget & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: tracking
  {
    out << "tracking: ";
    rosidl_generator_traits::value_to_yaml(msg.tracking, out);
    out << ", ";
  }

  // member: class_id
  {
    out << "class_id: ";
    rosidl_generator_traits::value_to_yaml(msg.class_id, out);
    out << ", ";
  }

  // member: score
  {
    out << "score: ";
    rosidl_generator_traits::value_to_yaml(msg.score, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << ", ";
  }

  // member: corners_uv
  {
    if (msg.corners_uv.size() == 0) {
      out << "corners_uv: []";
    } else {
      out << "corners_uv: [";
      size_t pending_items = msg.corners_uv.size();
      for (auto item : msg.corners_uv) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DetectedTarget & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: tracking
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tracking: ";
    rosidl_generator_traits::value_to_yaml(msg.tracking, out);
    out << "\n";
  }

  // member: class_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "class_id: ";
    rosidl_generator_traits::value_to_yaml(msg.class_id, out);
    out << "\n";
  }

  // member: score
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "score: ";
    rosidl_generator_traits::value_to_yaml(msg.score, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: corners_uv
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.corners_uv.size() == 0) {
      out << "corners_uv: []\n";
    } else {
      out << "corners_uv:\n";
      for (auto item : msg.corners_uv) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DetectedTarget & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace smarthome_vision

namespace rosidl_generator_traits
{

[[deprecated("use smarthome_vision::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const smarthome_vision::msg::DetectedTarget & msg,
  std::ostream & out, size_t indentation = 0)
{
  smarthome_vision::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use smarthome_vision::msg::to_yaml() instead")]]
inline std::string to_yaml(const smarthome_vision::msg::DetectedTarget & msg)
{
  return smarthome_vision::msg::to_yaml(msg);
}

template<>
inline const char * data_type<smarthome_vision::msg::DetectedTarget>()
{
  return "smarthome_vision::msg::DetectedTarget";
}

template<>
inline const char * name<smarthome_vision::msg::DetectedTarget>()
{
  return "smarthome_vision/msg/DetectedTarget";
}

template<>
struct has_fixed_size<smarthome_vision::msg::DetectedTarget>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<smarthome_vision::msg::DetectedTarget>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<smarthome_vision::msg::DetectedTarget>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__TRAITS_HPP_
