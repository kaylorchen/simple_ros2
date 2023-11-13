find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
add_executable(simple_ros2 simple_ros2.cpp)
ament_target_dependencies(simple_ros2 rclcpp)
install(TARGETS
        simple_ros2
        DESTINATION lib/${PROJECT_NAME})

find_package(std_msgs REQUIRED)
add_executable(single_subscriber single_subscriber.cpp)
ament_target_dependencies(single_subscriber rclcpp std_msgs)
install(TARGETS
        single_subscriber
        DESTINATION lib/${PROJECT_NAME})

add_executable(multi_subscribers multi_subscribers.cpp)
ament_target_dependencies(multi_subscribers rclcpp std_msgs)
install(TARGETS
        multi_subscribers
        DESTINATION lib/${PROJECT_NAME})

add_executable(talker talker.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
install(TARGETS
        talker
        DESTINATION lib/${PROJECT_NAME})