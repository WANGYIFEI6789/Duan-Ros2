cmake_minimum_required(VERSION 3.8)
project(CppNew)

add_executable(learn_auto learn_auto.cpp)
add_executable(learn_shared_ptr learn_shared_ptr.cpp)
add_executable(learn_lambda learn_lambda.cpp)
add_executable(learn_functional learn_functional.cpp)

# target_include_directories(ros2_cpp_node PUBLIC ${rclcpp_INCLUDE_DIRS})
# target_link_libraries(ros2_cpp_node ${rclcpp_LIBRARIES})