// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from smarthome_vision:msg/DetectedTarget.idl
// generated code does not contain a copyright notice

#ifndef SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__BUILDER_HPP_
#define SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "smarthome_vision/msg/detail/detected_target__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace smarthome_vision
{

namespace msg
{

namespace builder
{

class Init_DetectedTarget_corners_uv
{
public:
  explicit Init_DetectedTarget_corners_uv(::smarthome_vision::msg::DetectedTarget & msg)
  : msg_(msg)
  {}
  ::smarthome_vision::msg::DetectedTarget corners_uv(::smarthome_vision::msg::DetectedTarget::_corners_uv_type arg)
  {
    msg_.corners_uv = std::move(arg);
    return std::move(msg_);
  }

private:
  ::smarthome_vision::msg::DetectedTarget msg_;
};

class Init_DetectedTarget_z
{
public:
  explicit Init_DetectedTarget_z(::smarthome_vision::msg::DetectedTarget & msg)
  : msg_(msg)
  {}
  Init_DetectedTarget_corners_uv z(::smarthome_vision::msg::DetectedTarget::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_DetectedTarget_corners_uv(msg_);
  }

private:
  ::smarthome_vision::msg::DetectedTarget msg_;
};

class Init_DetectedTarget_y
{
public:
  explicit Init_DetectedTarget_y(::smarthome_vision::msg::DetectedTarget & msg)
  : msg_(msg)
  {}
  Init_DetectedTarget_z y(::smarthome_vision::msg::DetectedTarget::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_DetectedTarget_z(msg_);
  }

private:
  ::smarthome_vision::msg::DetectedTarget msg_;
};

class Init_DetectedTarget_x
{
public:
  explicit Init_DetectedTarget_x(::smarthome_vision::msg::DetectedTarget & msg)
  : msg_(msg)
  {}
  Init_DetectedTarget_y x(::smarthome_vision::msg::DetectedTarget::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_DetectedTarget_y(msg_);
  }

private:
  ::smarthome_vision::msg::DetectedTarget msg_;
};

class Init_DetectedTarget_score
{
public:
  explicit Init_DetectedTarget_score(::smarthome_vision::msg::DetectedTarget & msg)
  : msg_(msg)
  {}
  Init_DetectedTarget_x score(::smarthome_vision::msg::DetectedTarget::_score_type arg)
  {
    msg_.score = std::move(arg);
    return Init_DetectedTarget_x(msg_);
  }

private:
  ::smarthome_vision::msg::DetectedTarget msg_;
};

class Init_DetectedTarget_class_id
{
public:
  explicit Init_DetectedTarget_class_id(::smarthome_vision::msg::DetectedTarget & msg)
  : msg_(msg)
  {}
  Init_DetectedTarget_score class_id(::smarthome_vision::msg::DetectedTarget::_class_id_type arg)
  {
    msg_.class_id = std::move(arg);
    return Init_DetectedTarget_score(msg_);
  }

private:
  ::smarthome_vision::msg::DetectedTarget msg_;
};

class Init_DetectedTarget_tracking
{
public:
  explicit Init_DetectedTarget_tracking(::smarthome_vision::msg::DetectedTarget & msg)
  : msg_(msg)
  {}
  Init_DetectedTarget_class_id tracking(::smarthome_vision::msg::DetectedTarget::_tracking_type arg)
  {
    msg_.tracking = std::move(arg);
    return Init_DetectedTarget_class_id(msg_);
  }

private:
  ::smarthome_vision::msg::DetectedTarget msg_;
};

class Init_DetectedTarget_stamp
{
public:
  Init_DetectedTarget_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectedTarget_tracking stamp(::smarthome_vision::msg::DetectedTarget::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_DetectedTarget_tracking(msg_);
  }

private:
  ::smarthome_vision::msg::DetectedTarget msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::smarthome_vision::msg::DetectedTarget>()
{
  return smarthome_vision::msg::builder::Init_DetectedTarget_stamp();
}

}  // namespace smarthome_vision

#endif  // SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__BUILDER_HPP_
