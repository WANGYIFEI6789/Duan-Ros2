// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from status_interfaces:msg/SystemStatus.idl
// generated code does not contain a copyright notice
#include "status_interfaces/msg/detail/system_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `host_name`
#include "rosidl_runtime_c/string_functions.h"

bool
status_interfaces__msg__SystemStatus__init(status_interfaces__msg__SystemStatus * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    status_interfaces__msg__SystemStatus__fini(msg);
    return false;
  }
  // host_name
  if (!rosidl_runtime_c__String__init(&msg->host_name)) {
    status_interfaces__msg__SystemStatus__fini(msg);
    return false;
  }
  // cpu_percent
  // memory_percent
  // memory_total
  // memory_available
  // net_sent
  // net_recv
  return true;
}

void
status_interfaces__msg__SystemStatus__fini(status_interfaces__msg__SystemStatus * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // host_name
  rosidl_runtime_c__String__fini(&msg->host_name);
  // cpu_percent
  // memory_percent
  // memory_total
  // memory_available
  // net_sent
  // net_recv
}

bool
status_interfaces__msg__SystemStatus__are_equal(const status_interfaces__msg__SystemStatus * lhs, const status_interfaces__msg__SystemStatus * rhs)
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
  // host_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->host_name), &(rhs->host_name)))
  {
    return false;
  }
  // cpu_percent
  if (lhs->cpu_percent != rhs->cpu_percent) {
    return false;
  }
  // memory_percent
  if (lhs->memory_percent != rhs->memory_percent) {
    return false;
  }
  // memory_total
  if (lhs->memory_total != rhs->memory_total) {
    return false;
  }
  // memory_available
  if (lhs->memory_available != rhs->memory_available) {
    return false;
  }
  // net_sent
  if (lhs->net_sent != rhs->net_sent) {
    return false;
  }
  // net_recv
  if (lhs->net_recv != rhs->net_recv) {
    return false;
  }
  return true;
}

bool
status_interfaces__msg__SystemStatus__copy(
  const status_interfaces__msg__SystemStatus * input,
  status_interfaces__msg__SystemStatus * output)
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
  // host_name
  if (!rosidl_runtime_c__String__copy(
      &(input->host_name), &(output->host_name)))
  {
    return false;
  }
  // cpu_percent
  output->cpu_percent = input->cpu_percent;
  // memory_percent
  output->memory_percent = input->memory_percent;
  // memory_total
  output->memory_total = input->memory_total;
  // memory_available
  output->memory_available = input->memory_available;
  // net_sent
  output->net_sent = input->net_sent;
  // net_recv
  output->net_recv = input->net_recv;
  return true;
}

status_interfaces__msg__SystemStatus *
status_interfaces__msg__SystemStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  status_interfaces__msg__SystemStatus * msg = (status_interfaces__msg__SystemStatus *)allocator.allocate(sizeof(status_interfaces__msg__SystemStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(status_interfaces__msg__SystemStatus));
  bool success = status_interfaces__msg__SystemStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
status_interfaces__msg__SystemStatus__destroy(status_interfaces__msg__SystemStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    status_interfaces__msg__SystemStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
status_interfaces__msg__SystemStatus__Sequence__init(status_interfaces__msg__SystemStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  status_interfaces__msg__SystemStatus * data = NULL;

  if (size) {
    data = (status_interfaces__msg__SystemStatus *)allocator.zero_allocate(size, sizeof(status_interfaces__msg__SystemStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = status_interfaces__msg__SystemStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        status_interfaces__msg__SystemStatus__fini(&data[i - 1]);
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
status_interfaces__msg__SystemStatus__Sequence__fini(status_interfaces__msg__SystemStatus__Sequence * array)
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
      status_interfaces__msg__SystemStatus__fini(&array->data[i]);
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

status_interfaces__msg__SystemStatus__Sequence *
status_interfaces__msg__SystemStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  status_interfaces__msg__SystemStatus__Sequence * array = (status_interfaces__msg__SystemStatus__Sequence *)allocator.allocate(sizeof(status_interfaces__msg__SystemStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = status_interfaces__msg__SystemStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
status_interfaces__msg__SystemStatus__Sequence__destroy(status_interfaces__msg__SystemStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    status_interfaces__msg__SystemStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
status_interfaces__msg__SystemStatus__Sequence__are_equal(const status_interfaces__msg__SystemStatus__Sequence * lhs, const status_interfaces__msg__SystemStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!status_interfaces__msg__SystemStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
status_interfaces__msg__SystemStatus__Sequence__copy(
  const status_interfaces__msg__SystemStatus__Sequence * input,
  status_interfaces__msg__SystemStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(status_interfaces__msg__SystemStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    status_interfaces__msg__SystemStatus * data =
      (status_interfaces__msg__SystemStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!status_interfaces__msg__SystemStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          status_interfaces__msg__SystemStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!status_interfaces__msg__SystemStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
