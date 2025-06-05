// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from status_interfaces:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#ifndef STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__TRAITS_HPP_
#define STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "status_interfaces/msg/detail/system_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace status_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SystemStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: host_name
  {
    out << "host_name: ";
    rosidl_generator_traits::value_to_yaml(msg.host_name, out);
    out << ", ";
  }

  // member: cpu_percent
  {
    out << "cpu_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.cpu_percent, out);
    out << ", ";
  }

  // member: memory_percent
  {
    out << "memory_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.memory_percent, out);
    out << ", ";
  }

  // member: memory_total
  {
    out << "memory_total: ";
    rosidl_generator_traits::value_to_yaml(msg.memory_total, out);
    out << ", ";
  }

  // member: memory_available
  {
    out << "memory_available: ";
    rosidl_generator_traits::value_to_yaml(msg.memory_available, out);
    out << ", ";
  }

  // member: net_sent
  {
    out << "net_sent: ";
    rosidl_generator_traits::value_to_yaml(msg.net_sent, out);
    out << ", ";
  }

  // member: net_recv
  {
    out << "net_recv: ";
    rosidl_generator_traits::value_to_yaml(msg.net_recv, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SystemStatus & msg,
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

  // member: host_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "host_name: ";
    rosidl_generator_traits::value_to_yaml(msg.host_name, out);
    out << "\n";
  }

  // member: cpu_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cpu_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.cpu_percent, out);
    out << "\n";
  }

  // member: memory_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "memory_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.memory_percent, out);
    out << "\n";
  }

  // member: memory_total
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "memory_total: ";
    rosidl_generator_traits::value_to_yaml(msg.memory_total, out);
    out << "\n";
  }

  // member: memory_available
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "memory_available: ";
    rosidl_generator_traits::value_to_yaml(msg.memory_available, out);
    out << "\n";
  }

  // member: net_sent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "net_sent: ";
    rosidl_generator_traits::value_to_yaml(msg.net_sent, out);
    out << "\n";
  }

  // member: net_recv
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "net_recv: ";
    rosidl_generator_traits::value_to_yaml(msg.net_recv, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SystemStatus & msg, bool use_flow_style = false)
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

}  // namespace status_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use status_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const status_interfaces::msg::SystemStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  status_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use status_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const status_interfaces::msg::SystemStatus & msg)
{
  return status_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<status_interfaces::msg::SystemStatus>()
{
  return "status_interfaces::msg::SystemStatus";
}

template<>
inline const char * name<status_interfaces::msg::SystemStatus>()
{
  return "status_interfaces/msg/SystemStatus";
}

template<>
struct has_fixed_size<status_interfaces::msg::SystemStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<status_interfaces::msg::SystemStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<status_interfaces::msg::SystemStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // STATUS_INTERFACES__MSG__DETAIL__SYSTEM_STATUS__TRAITS_HPP_
