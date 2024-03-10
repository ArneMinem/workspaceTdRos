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
find_package(visualization_msgs REQUIRED)
find_package(tf2_ros REQUIRED)

add_executable(NodeSimu
  src/NodeSimu.cpp
  src/main_NS.cpp
)
ament_target_dependencies(NodeSimu rclcpp example_interfaces tf2 tf2_geometry_msgs geometry_msgs visualization_msgs tf2_ros)
target_link_libraries(NodeSimu "${cpp_typesupport_target}")
target_include_directories(NodeSimu PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)

add_executable(NodeControl
  src/NodeControl.cpp
  src/main_NC.cpp
)
ament_target_dependencies(NodeControl rclcpp example_interfaces tf2 tf2_geometry_msgs geometry_msgs visualization_msgs)
target_link_libraries(NodeControl "${cpp_typesupport_target}")
target_include_directories(NodeControl PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)

add_executable(NodeCible
  src/NodeCible.cpp
  src/main_NCi.cpp
)
ament_target_dependencies(NodeCible rclcpp example_interfaces tf2 tf2_geometry_msgs geometry_msgs visualization_msgs)
target_link_libraries(NodeCible "${cpp_typesupport_target}")
target_include_directories(NodeCible PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)

add_executable(NodeTourelle
  src/NodeTourelle.cpp
  src/main_NT.cpp
)
ament_target_dependencies(NodeTourelle rclcpp example_interfaces tf2 tf2_geometry_msgs geometry_msgs visualization_msgs tf2_ros)
target_link_libraries(NodeTourelle "${cpp_typesupport_target}")
target_include_directories(NodeTourelle PUBLIC
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

install(TARGETS NodeControl
DESTINATION lib/${PROJECT_NAME})

install(TARGETS NodeCible
DESTINATION lib/${PROJECT_NAME})

install(TARGETS NodeTourelle
DESTINATION lib/${PROJECT_NAME})

ament_package()
