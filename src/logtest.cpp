#include "iostream"
#include "rclcpp/rclcpp.hpp"
#include "stdio.h"
#include "unistd.h"

std::string string_thread_id() {
  auto hashed = std::hash<std::thread::id>()(std::this_thread::get_id());
  return std::to_string(hashed);
}

class mynode : public rclcpp::Node {
 public:
  mynode(std::string&& name) : Node(name) {
    RCLCPP_INFO_STREAM(this->get_logger(), "this is constructor");
    std::thread t1(std::bind(&mynode::test_thread, this));
    std::thread t2(std::bind(&mynode::test_thread, this));
    std::thread t3([this]() {
      RCLCPP_INFO(this->get_logger(),
                  "Lamda log test, PID = %d, thread id is %s", getpid(),
                  string_thread_id().c_str());
    });
    t1.join();
    t2.join();
    t3.join();
  }
  ~mynode() { RCLCPP_INFO(this->get_logger(), "this is destructor"); }

  void test_thread() {
    RCLCPP_INFO(this->get_logger(), "PID = %d, thread id is %s", getpid(),
                string_thread_id().c_str());
  }
};

void thread3_callback(rclcpp::Node* node) {
  RCLCPP_INFO(node->get_logger(), "thread3 test");
}

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  std::cout << "C++ iostream output" << std::endl;
  printf("this is printf\n");
  fprintf(stderr, "stderr output\n");
  fprintf(stdout, "stdout output\n");
  //  auto node = std::make_shared<mynode>();
  auto node = new mynode("kaylor");
  RCLCPP_DEBUG(node->get_logger(), "RCLCPP DEBUG");
  RCLCPP_INFO(node->get_logger(), "RCLCPP INFO");
  RCLCPP_WARN(node->get_logger(), "RCLCPP WARN");
  RCLCPP_ERROR(node->get_logger(), "RCLCPP ERROR");
  RCLCPP_FATAL(node->get_logger(), "RCLCPP FATAL");
  std::thread thread1(
      []() { RCLCPP_INFO(rclcpp::get_logger("thread1"), "thread1....."); });
  std::thread thread2(
      [node]() { RCLCPP_INFO(node->get_logger(), "thread2....."); });
  std::thread thread3(std::bind(&thread3_callback, node));
  thread1.join();
  thread2.join();
  thread3.join();
  fflush(stdout);
  delete node;
  RCLCPP_INFO(rclcpp::get_logger("node"), "11111111");
  RCLCPP_INFO(rclcpp::get_logger("root"), "22222222");
  std::cout << std::endl;
  rclcpp::shutdown();
  return 0;
}
