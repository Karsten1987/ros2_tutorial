#include <iostream>

#include "rclcpp/rclcpp.hpp"

#include "talker.hpp"
#include "listener.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto talker_node = std::make_shared<TalkerNode>();
  auto listener_node = std::make_shared<ListenerNode>();

  auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
  executor->add_node(talker_node);
  executor->add_node(listener_node);
  executor->spin();

  rclcpp::shutdown();

  return 0;
}
