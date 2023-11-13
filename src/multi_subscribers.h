#ifndef __MULTI_SUBSCRIBERS_H__
#define __MULTI_SUBSCRIBERS_H__

#include "rclcpp/rclcpp.hpp"

template <typename MessageT>
class MultiSubscribers {
 public:
  template <typename CallbackT>
  MultiSubscribers(rclcpp::Node &node, const std::string &topic_name,
                   CallbackT &&callback) {
    callback_group_subscriber_ = node.create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive);
    auto sub_opt = rclcpp::SubscriptionOptions();
    sub_opt.callback_group = callback_group_subscriber_;
    subscription_ = node.create_subscription<MessageT>(
        topic_name, rclcpp::QoS(10), std::forward<CallbackT>(callback),
        sub_opt);
  }

 private:
  rclcpp::CallbackGroup::SharedPtr callback_group_subscriber_;
  std::shared_ptr<rclcpp::Subscription<MessageT>> subscription_;
};
#endif