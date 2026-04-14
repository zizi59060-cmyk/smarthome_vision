// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from smarthome_vision:msg/DetectedTarget.idl
// generated code does not contain a copyright notice

#ifndef SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__FUNCTIONS_H_
#define SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "smarthome_vision/msg/rosidl_generator_c__visibility_control.h"

#include "smarthome_vision/msg/detail/detected_target__struct.h"

/// Initialize msg/DetectedTarget message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * smarthome_vision__msg__DetectedTarget
 * )) before or use
 * smarthome_vision__msg__DetectedTarget__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
bool
smarthome_vision__msg__DetectedTarget__init(smarthome_vision__msg__DetectedTarget * msg);

/// Finalize msg/DetectedTarget message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
void
smarthome_vision__msg__DetectedTarget__fini(smarthome_vision__msg__DetectedTarget * msg);

/// Create msg/DetectedTarget message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * smarthome_vision__msg__DetectedTarget__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
smarthome_vision__msg__DetectedTarget *
smarthome_vision__msg__DetectedTarget__create();

/// Destroy msg/DetectedTarget message.
/**
 * It calls
 * smarthome_vision__msg__DetectedTarget__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
void
smarthome_vision__msg__DetectedTarget__destroy(smarthome_vision__msg__DetectedTarget * msg);

/// Check for msg/DetectedTarget message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
bool
smarthome_vision__msg__DetectedTarget__are_equal(const smarthome_vision__msg__DetectedTarget * lhs, const smarthome_vision__msg__DetectedTarget * rhs);

/// Copy a msg/DetectedTarget message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
bool
smarthome_vision__msg__DetectedTarget__copy(
  const smarthome_vision__msg__DetectedTarget * input,
  smarthome_vision__msg__DetectedTarget * output);

/// Initialize array of msg/DetectedTarget messages.
/**
 * It allocates the memory for the number of elements and calls
 * smarthome_vision__msg__DetectedTarget__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
bool
smarthome_vision__msg__DetectedTarget__Sequence__init(smarthome_vision__msg__DetectedTarget__Sequence * array, size_t size);

/// Finalize array of msg/DetectedTarget messages.
/**
 * It calls
 * smarthome_vision__msg__DetectedTarget__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
void
smarthome_vision__msg__DetectedTarget__Sequence__fini(smarthome_vision__msg__DetectedTarget__Sequence * array);

/// Create array of msg/DetectedTarget messages.
/**
 * It allocates the memory for the array and calls
 * smarthome_vision__msg__DetectedTarget__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
smarthome_vision__msg__DetectedTarget__Sequence *
smarthome_vision__msg__DetectedTarget__Sequence__create(size_t size);

/// Destroy array of msg/DetectedTarget messages.
/**
 * It calls
 * smarthome_vision__msg__DetectedTarget__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
void
smarthome_vision__msg__DetectedTarget__Sequence__destroy(smarthome_vision__msg__DetectedTarget__Sequence * array);

/// Check for msg/DetectedTarget message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
bool
smarthome_vision__msg__DetectedTarget__Sequence__are_equal(const smarthome_vision__msg__DetectedTarget__Sequence * lhs, const smarthome_vision__msg__DetectedTarget__Sequence * rhs);

/// Copy an array of msg/DetectedTarget messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_smarthome_vision
bool
smarthome_vision__msg__DetectedTarget__Sequence__copy(
  const smarthome_vision__msg__DetectedTarget__Sequence * input,
  smarthome_vision__msg__DetectedTarget__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SMARTHOME_VISION__MSG__DETAIL__DETECTED_TARGET__FUNCTIONS_H_
