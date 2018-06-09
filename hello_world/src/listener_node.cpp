#include <iostream>

#include "rclcpp/rclcpp.hpp"

#include "listener.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto listener_node = std::make_shared<ListenerNode>();

  rclcpp::spin(listener_node);

  rclcpp::shutdown();
}
