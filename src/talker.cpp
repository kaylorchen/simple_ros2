#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node {
 public:
  MinimalPublisher() : Node("minimal_publisher"), count_(0) {
    publisher1_ = this->create_publisher<std_msgs::msg::String>("topic1", 10);
    timer1_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer1_callback, this));
    publisher2_ = this->create_publisher<std_msgs::msg::String>("topic2", 10);
    timer2_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer2_callback, this));
  }

 private:
  std::string string_thread_id() {
    auto hashed = std::hash<std::thread::id>()(std::this_thread::get_id());
    return std::to_string(hashed);
  }

  void timer1_callback() {
    auto message = std_msgs::msg::String();
    std::lock_guard<std::mutex> lock(count_mutex_);
    message.data = "Hello, world! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s', thread id = %s",
                message.data.c_str(), string_thread_id().c_str());
    publisher1_->publish(message);
  }
  void timer2_callback() {
    auto message = std_msgs::msg::String();
    std::lock_guard<std::mutex> lock(count_mutex_);
    message.data = "Hello, world! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s', thread id = %s",
                message.data.c_str(), string_thread_id().c_str());
    publisher2_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer1_;
  rclcpp::TimerBase::SharedPtr timer2_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher1_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher2_;
  size_t count_;
  std::mutex count_mutex_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}