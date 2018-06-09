#ifndef LISTENER_INTRAPROCESS_HPP_
#define LISTENER_INTRAPROCESS_HPP_

#include <chrono>

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class ListenerNode : public rclcpp::Node
{
public:
  ListenerNode():
    rclcpp::Node("listener_node", "hello_world_namespace", true)
  {
    // use of unique_ptr instead of shared_ptr
    auto subscribe_lamdba = [&](std::unique_ptr<std_msgs::msg::String> msg) -> void {
        RCLCPP_INFO(this->get_logger(), "Receiving: '%s'", msg->data.c_str())
        RCLCPP_INFO(this->get_logger(), "Pointer Address: '%p'", msg.get())
      };

    sub_ = this->create_subscription<std_msgs::msg::String>(
      "hello_world_topic", subscribe_lamdba);  // <-- lambda function as callback
  }

private:
  std::shared_ptr<rclcpp::Subscription<std_msgs::msg::String>> sub_;
};

#endif
