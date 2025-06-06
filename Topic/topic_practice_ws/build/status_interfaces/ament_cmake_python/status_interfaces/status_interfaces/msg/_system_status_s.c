// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from status_interfaces:msg/SystemStatus.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "status_interfaces/msg/detail/system_status__struct.h"
#include "status_interfaces/msg/detail/system_status__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool status_interfaces__msg__system_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[50];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("status_interfaces.msg._system_status.SystemStatus", full_classname_dest, 49) == 0);
  }
  status_interfaces__msg__SystemStatus * ros_message = _ros_message;
  {  // stamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "stamp");
    if (!field) {
      return false;
    }
    if (!builtin_interfaces__msg__time__convert_from_py(field, &ros_message->stamp)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // host_name
    PyObject * field = PyObject_GetAttrString(_pymsg, "host_name");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->host_name, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // cpu_percent
    PyObject * field = PyObject_GetAttrString(_pymsg, "cpu_percent");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->cpu_percent = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // memory_percent
    PyObject * field = PyObject_GetAttrString(_pymsg, "memory_percent");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->memory_percent = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // memory_total
    PyObject * field = PyObject_GetAttrString(_pymsg, "memory_total");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->memory_total = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // memory_available
    PyObject * field = PyObject_GetAttrString(_pymsg, "memory_available");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->memory_available = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // net_sent
    PyObject * field = PyObject_GetAttrString(_pymsg, "net_sent");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->net_sent = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // net_recv
    PyObject * field = PyObject_GetAttrString(_pymsg, "net_recv");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->net_recv = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * status_interfaces__msg__system_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SystemStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("status_interfaces.msg._system_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SystemStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  status_interfaces__msg__SystemStatus * ros_message = (status_interfaces__msg__SystemStatus *)raw_ros_message;
  {  // stamp
    PyObject * field = NULL;
    field = builtin_interfaces__msg__time__convert_to_py(&ros_message->stamp);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "stamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // host_name
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->host_name.data,
      strlen(ros_message->host_name.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "host_name", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // cpu_percent
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->cpu_percent);
    {
      int rc = PyObject_SetAttrString(_pymessage, "cpu_percent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // memory_percent
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->memory_percent);
    {
      int rc = PyObject_SetAttrString(_pymessage, "memory_percent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // memory_total
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->memory_total);
    {
      int rc = PyObject_SetAttrString(_pymessage, "memory_total", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // memory_available
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->memory_available);
    {
      int rc = PyObject_SetAttrString(_pymessage, "memory_available", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // net_sent
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->net_sent);
    {
      int rc = PyObject_SetAttrString(_pymessage, "net_sent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // net_recv
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->net_recv);
    {
      int rc = PyObject_SetAttrString(_pymessage, "net_recv", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
