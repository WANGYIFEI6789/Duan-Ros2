# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_duanbot_navigation2_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED duanbot_navigation2_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(duanbot_navigation2_FOUND FALSE)
  elseif(NOT duanbot_navigation2_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(duanbot_navigation2_FOUND FALSE)
  endif()
  return()
endif()
set(_duanbot_navigation2_CONFIG_INCLUDED TRUE)

# output package information
if(NOT duanbot_navigation2_FIND_QUIETLY)
  message(STATUS "Found duanbot_navigation2: 0.0.0 (${duanbot_navigation2_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'duanbot_navigation2' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${duanbot_navigation2_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(duanbot_navigation2_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${duanbot_navigation2_DIR}/${_extra}")
endforeach()
