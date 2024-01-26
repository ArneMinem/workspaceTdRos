cmake_minimum_required(VERSION 3.8)
project(td2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(tf2 REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

add_executable(NodeSimu
  src/NodeSimu.cpp
  src/td2.cpp
)
ament_target_dependencies(NodeSimu rclcpp rclcpp example_interfaces tf2 tf2_geometry_msgs geometry_msgs)
target_link_libraries(NodeSimu "${cpp_typesupport_target}")
target_include_directories(NodeSimu PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)

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

install(TARGETS NodeSimu
DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
DESTINATION share/${PROJECT_NAME}/
)

install(DIRECTORY config
DESTINATION share/${PROJECT_NAME}/
)

install(DIRECTORY meshes
DESTINATION share/${PROJECT_NAME}/
)

ament_package()
