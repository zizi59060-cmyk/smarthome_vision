// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from smarthome_vision:msg/DetectedTarget.idl
// generated code does not contain a copyright notice
#include "smarthome_vision/msg/detail/detected_target__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `corners_uv`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
smarthome_vision__msg__DetectedTarget__init(smarthome_vision__msg__DetectedTarget * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    smarthome_vision__msg__DetectedTarget__fini(msg);
    return false;
  }
  // mode
  // tracking
  // class_id
  // score
  // x
  // y
  // z
  // corners_uv
  if (!rosidl_runtime_c__float__Sequence__init(&msg->corners_uv, 0)) {
    smarthome_vision__msg__DetectedTarget__fini(msg);
    return false;
  }
  return true;
}

void
smarthome_vision__msg__DetectedTarget__fini(smarthome_vision__msg__DetectedTarget * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // mode
  // tracking
  // class_id
  // score
  // x
  // y
  // z
  // corners_uv
  rosidl_runtime_c__float__Sequence__fini(&msg->corners_uv);
}

bool
smarthome_vision__msg__DetectedTarget__are_equal(const smarthome_vision__msg__DetectedTarget * lhs, const smarthome_vision__msg__DetectedTarget * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // tracking
  if (lhs->tracking != rhs->tracking) {
    return false;
  }
  // class_id
  if (lhs->class_id != rhs->class_id) {
    return false;
  }
  // score
  if (lhs->score != rhs->score) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  // corners_uv
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->corners_uv), &(rhs->corners_uv)))
  {
    return false;
  }
  return true;
}

bool
smarthome_vision__msg__DetectedTarget__copy(
  const smarthome_vision__msg__DetectedTarget * input,
  smarthome_vision__msg__DetectedTarget * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // mode
  output->mode = input->mode;
  // tracking
  output->tracking = input->tracking;
  // class_id
  output->class_id = input->class_id;
  // score
  output->score = input->score;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // z
  output->z = input->z;
  // corners_uv
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->corners_uv), &(output->corners_uv)))
  {
    return false;
  }
  return true;
}

smarthome_vision__msg__DetectedTarget *
smarthome_vision__msg__DetectedTarget__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  smarthome_vision__msg__DetectedTarget * msg = (smarthome_vision__msg__DetectedTarget *)allocator.allocate(sizeof(smarthome_vision__msg__DetectedTarget), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(smarthome_vision__msg__DetectedTarget));
  bool success = smarthome_vision__msg__DetectedTarget__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
smarthome_vision__msg__DetectedTarget__destroy(smarthome_vision__msg__DetectedTarget * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    smarthome_vision__msg__DetectedTarget__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
smarthome_vision__msg__DetectedTarget__Sequence__init(smarthome_vision__msg__DetectedTarget__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  smarthome_vision__msg__DetectedTarget * data = NULL;

  if (size) {
    data = (smarthome_vision__msg__DetectedTarget *)allocator.zero_allocate(size, sizeof(smarthome_vision__msg__DetectedTarget), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = smarthome_vision__msg__DetectedTarget__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        smarthome_vision__msg__DetectedTarget__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
smarthome_vision__msg__DetectedTarget__Sequence__fini(smarthome_vision__msg__DetectedTarget__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      smarthome_vision__msg__DetectedTarget__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

smarthome_vision__msg__DetectedTarget__Sequence *
smarthome_vision__msg__DetectedTarget__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  smarthome_vision__msg__DetectedTarget__Sequence * array = (smarthome_vision__msg__DetectedTarget__Sequence *)allocator.allocate(sizeof(smarthome_vision__msg__DetectedTarget__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = smarthome_vision__msg__DetectedTarget__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
smarthome_vision__msg__DetectedTarget__Sequence__destroy(smarthome_vision__msg__DetectedTarget__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    smarthome_vision__msg__DetectedTarget__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
smarthome_vision__msg__DetectedTarget__Sequence__are_equal(const smarthome_vision__msg__DetectedTarget__Sequence * lhs, const smarthome_vision__msg__DetectedTarget__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!smarthome_vision__msg__DetectedTarget__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
smarthome_vision__msg__DetectedTarget__Sequence__copy(
  const smarthome_vision__msg__DetectedTarget__Sequence * input,
  smarthome_vision__msg__DetectedTarget__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(smarthome_vision__msg__DetectedTarget);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    smarthome_vision__msg__DetectedTarget * data =
      (smarthome_vision__msg__DetectedTarget *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!smarthome_vision__msg__DetectedTarget__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          smarthome_vision__msg__DetectedTarget__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!smarthome_vision__msg__DetectedTarget__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
