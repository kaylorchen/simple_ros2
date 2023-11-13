#include "multi_subscribers.h"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
 public:
  MinimalSubscriber() : Node("multi_subscribers") {
    sub1 = std::make_shared<MultiSubscribers<std_msgs::msg::String>>(*this, "topic1",std::bind(&MinimalSubscriber::topic1_callback, this, _1));
    sub2 = std::make_shared<MultiSubscribers<std_msgs::msg::String>>(*this, "topic2",std::bind(&MinimalSubscriber::topic2_callback, this, _1));
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
  std::shared_ptr<MultiSubscribers<std_msgs::msg::String>> sub1;
  std::shared_ptr<MultiSubscribers<std_msgs::msg::String>> sub2;
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor executor(rclcpp::ExecutorOptions(), 2, false, std::chrono::nanoseconds(-1));
    auto node = std::make_shared<MinimalSubscriber>();
    executor.add_node(node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}