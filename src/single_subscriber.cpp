#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
 public:
  MinimalSubscriber() : Node("minimal_subscriber") {
    subscription1_ = this->create_subscription<std_msgs::msg::String>(
        "topic1", 10, std::bind(&MinimalSubscriber::topic1_callback, this, _1));
    subscription2_ = this->create_subscription<std_msgs::msg::String>(
        "topic2", 10, std::bind(&MinimalSubscriber::topic2_callback, this, _1));
  }

 private:
  std::string string_thread_id() {
    auto hashed = std::hash<std::thread::id>()(std::this_thread::get_id());
    return std::to_string(hashed);
  }
  void topic1_callback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "callback1: I heard: '%s', thread id = %s",
                msg->data.c_str(), string_thread_id().c_str());
  }
  void topic2_callback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "callback2: I heard: '%s', thread id = %s",
                msg->data.c_str(), string_thread_id().c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription1_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription2_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}