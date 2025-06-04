cmake_minimum_required(VERSION 3.8)
project(demo_turtle_topic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

# 创建功能包的时候 已经指定了依赖 所以已经find_package了 不用我们自己加了
# 我们只需要在find_package下面添加可执行文件 给文件添加依赖即可
add_executable(turtle_circle src/turtle_circle.cpp)
# 添加依赖
ament_target_dependencies(turtle_circle rclcpp geometry_msgs)

add_executable(turtle_control src/turtle_control.cpp)
ament_target_dependencies(turtle_control rclcpp geometry_msgs turtlesim)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# install 拷贝到install下 source环境变量 才可以ros2 run
install(TARGETS turtle_circle
DESTINATION lib/${PROJECT_NAME}
)

# install 拷贝到install下 source环境变量 才可以ros2 run
install(TARGETS turtle_control
DESTINATION lib/${PROJECT_NAME}
)

ament_package()
