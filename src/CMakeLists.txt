find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
add_executable(simple_ros2 simple_ros2.cpp)
ament_target_dependencies(simple_ros2 rclcpp)
install(TARGETS
        simple_ros2
        DESTINATION lib/${PROJECT_NAME})