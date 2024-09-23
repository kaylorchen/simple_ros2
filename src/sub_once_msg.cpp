//
// Created by kaylor on 9/23/24.
//
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/wait_for_message.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include "chrono"

int main(int argc, char **argv){
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("root");
  sensor_msgs::msg::CameraInfo msg;
  std::string topic = "/camera_01/color/camera_info";
  if(rclcpp::wait_for_message<sensor_msgs::msg::CameraInfo>(msg, node, topic, std::chrono::seconds(10))){
    RCLCPP_INFO(node->get_logger(), "received message");
    for (auto &item: msg.k) {
      RCLCPP_INFO(node->get_logger(), "K: %f", item);
    }
  }
  return 0;
}