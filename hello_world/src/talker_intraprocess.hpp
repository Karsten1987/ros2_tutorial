#ifndef TALKER_HPP_
#define TALKER_HPP_

#include <chrono>

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class TalkerNode : public rclcpp::Node
{
public:
  TalkerNode():
    rclcpp::Node("talker_node", "hello_world_namespace", true)  // true for intraprocess
  {
    msg_ = std::make_unique<std_msgs::msg::String>();
    pub_ = this->create_publisher<std_msgs::msg::String>("hello_world_topic");
    timer_ = this->create_wall_timer(1s, std::bind(&TalkerNode::publish, this));
  }

  void publish() {
    static int i = 0;
    // make unique again!
    // after first publish, the unique_ptr dangles
    msg_ = std::make_unique<std_msgs::msg::String>();
    msg_->data = "Hello World " + std::to_string(i++);

    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg_->data.c_str())
    RCLCPP_INFO(this->get_logger(), "Pointer Address: '%p'", msg_.get())
    pub_->publish(msg_);
  }

private:
  std::unique_ptr<std_msgs::msg::String> msg_;
  std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String>> pub_;
  std::shared_ptr<rclcpp::TimerBase> timer_;
};

#endif
