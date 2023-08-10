#include "iostream"
#include "rclcpp/rclcpp.hpp"
#include "stdio.h"

class mynode : public rclcpp::Node {
 public:
  mynode() : Node("node") {}
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  std::cout << "C++ iostream output" << std::endl;
  printf("this is printf\n");
  fprintf(stderr, "stderr output\n");
  fprintf(stdout, "stdout output\n");
  auto node = std::make_shared<mynode>();
  RCLCPP_DEBUG(node->get_logger(), "RCLCPP DEBUG");
  RCLCPP_INFO(node->get_logger(), "RCLCPP INFO");
  RCLCPP_WARN(node->get_logger(), "RCLCPP WARN");
  RCLCPP_ERROR(node->get_logger(), "RCLCPP ERROR");
  RCLCPP_FATAL(node->get_logger(), "RCLCPP FATAL");
  fflush(stdout);
  rclcpp::shutdown();
  exit(EXIT_FAILURE);
  return 0;
}