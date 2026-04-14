// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from smarthome_vision:msg/DetectedTarget.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "smarthome_vision/msg/detail/detected_target__rosidl_typesupport_introspection_c.h"
#include "smarthome_vision/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "smarthome_vision/msg/detail/detected_target__functions.h"
#include "smarthome_vision/msg/detail/detected_target__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `corners_uv`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  smarthome_vision__msg__DetectedTarget__init(message_memory);
}

void smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_fini_function(void * message_memory)
{
  smarthome_vision__msg__DetectedTarget__fini(message_memory);
}

size_t smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__size_function__DetectedTarget__corners_uv(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__get_const_function__DetectedTarget__corners_uv(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__get_function__DetectedTarget__corners_uv(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__fetch_function__DetectedTarget__corners_uv(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__get_const_function__DetectedTarget__corners_uv(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__assign_function__DetectedTarget__corners_uv(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__get_function__DetectedTarget__corners_uv(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__resize_function__DetectedTarget__corners_uv(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_member_array[8] = {
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smarthome_vision__msg__DetectedTarget, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tracking",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smarthome_vision__msg__DetectedTarget, tracking),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "class_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smarthome_vision__msg__DetectedTarget, class_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "score",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smarthome_vision__msg__DetectedTarget, score),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smarthome_vision__msg__DetectedTarget, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smarthome_vision__msg__DetectedTarget, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "z",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smarthome_vision__msg__DetectedTarget, z),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "corners_uv",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smarthome_vision__msg__DetectedTarget, corners_uv),  // bytes offset in struct
    NULL,  // default value
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__size_function__DetectedTarget__corners_uv,  // size() function pointer
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__get_const_function__DetectedTarget__corners_uv,  // get_const(index) function pointer
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__get_function__DetectedTarget__corners_uv,  // get(index) function pointer
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__fetch_function__DetectedTarget__corners_uv,  // fetch(index, &value) function pointer
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__assign_function__DetectedTarget__corners_uv,  // assign(index, value) function pointer
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__resize_function__DetectedTarget__corners_uv  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_members = {
  "smarthome_vision__msg",  // message namespace
  "DetectedTarget",  // message name
  8,  // number of fields
  sizeof(smarthome_vision__msg__DetectedTarget),
  smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_member_array,  // message members
  smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_init_function,  // function to initialize message memory (memory has to be allocated)
  smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_type_support_handle = {
  0,
  &smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_smarthome_vision
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, smarthome_vision, msg, DetectedTarget)() {
  smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_type_support_handle.typesupport_identifier) {
    smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &smarthome_vision__msg__DetectedTarget__rosidl_typesupport_introspection_c__DetectedTarget_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
