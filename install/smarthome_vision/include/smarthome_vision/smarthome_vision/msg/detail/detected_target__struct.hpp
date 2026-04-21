// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from smarthome_vision:msg/DetectedTarget.idl
// generated code does not contain a copyright notice

#ifndef SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__STRUCT_HPP_
#define SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__smarthome_vision__msg__DetectedTarget __attribute__((deprecated))
#else
# define DEPRECATED__smarthome_vision__msg__DetectedTarget __declspec(deprecated)
#endif

namespace smarthome_vision
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DetectedTarget_
{
  using Type = DetectedTarget_<ContainerAllocator>;

  explicit DetectedTarget_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->tracking = false;
      this->class_id = 0l;
      this->score = 0.0f;
      this->x = 0.0f;
      this->y = 0.0f;
      this->z = 0.0f;
    }
  }

  explicit DetectedTarget_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->tracking = false;
      this->class_id = 0l;
      this->score = 0.0f;
      this->x = 0.0f;
      this->y = 0.0f;
      this->z = 0.0f;
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _tracking_type =
    bool;
  _tracking_type tracking;
  using _class_id_type =
    int32_t;
  _class_id_type class_id;
  using _score_type =
    float;
  _score_type score;
  using _x_type =
    float;
  _x_type x;
  using _y_type =
    float;
  _y_type y;
  using _z_type =
    float;
  _z_type z;
  using _corners_uv_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _corners_uv_type corners_uv;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__tracking(
    const bool & _arg)
  {
    this->tracking = _arg;
    return *this;
  }
  Type & set__class_id(
    const int32_t & _arg)
  {
    this->class_id = _arg;
    return *this;
  }
  Type & set__score(
    const float & _arg)
  {
    this->score = _arg;
    return *this;
  }
  Type & set__x(
    const float & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const float & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__z(
    const float & _arg)
  {
    this->z = _arg;
    return *this;
  }
  Type & set__corners_uv(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->corners_uv = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    smarthome_vision::msg::DetectedTarget_<ContainerAllocator> *;
  using ConstRawPtr =
    const smarthome_vision::msg::DetectedTarget_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<smarthome_vision::msg::DetectedTarget_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<smarthome_vision::msg::DetectedTarget_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      smarthome_vision::msg::DetectedTarget_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<smarthome_vision::msg::DetectedTarget_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      smarthome_vision::msg::DetectedTarget_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<smarthome_vision::msg::DetectedTarget_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<smarthome_vision::msg::DetectedTarget_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<smarthome_vision::msg::DetectedTarget_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__smarthome_vision__msg__DetectedTarget
    std::shared_ptr<smarthome_vision::msg::DetectedTarget_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__smarthome_vision__msg__DetectedTarget
    std::shared_ptr<smarthome_vision::msg::DetectedTarget_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetectedTarget_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    if (this->tracking != other.tracking) {
      return false;
    }
    if (this->class_id != other.class_id) {
      return false;
    }
    if (this->score != other.score) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    if (this->corners_uv != other.corners_uv) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetectedTarget_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetectedTarget_

// alias to use template instance with default allocator
using DetectedTarget =
  smarthome_vision::msg::DetectedTarget_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace smarthome_vision

#endif  // SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__STRUCT_HPP_
