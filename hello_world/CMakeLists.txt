cmake_minimum_required(VERSION 3.5)
project(hello_world)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(talker_node src/talker_node.cpp)
ament_target_dependencies(
  talker_node
  rclcpp
  std_msgs
)

add_executable(listener_node src/listener_node.cpp)
ament_target_dependencies(
  listener_node
  rclcpp
  std_msgs
)

add_executable(talker_listener_node src/talker_listener_node.cpp)
ament_target_dependencies(
  talker_listener_node
  rclcpp
  std_msgs
)

add_executable(talker_listener_intraprocess_node src/talker_listener_intraprocess_node.cpp)
ament_target_dependencies(
  talker_listener_intraprocess_node
  rclcpp
  std_msgs
)

install(
  TARGETS talker_node listener_node talker_listener_node talker_listener_intraprocess_node
  DESTINATION lib/${PROJECT_NAME}
)

install(
  FILES src/hello_world/talker.py src/hello_world/listener.py
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # remove the line when a copyright and license is present in all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # remove the line when this package is a git repo
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
