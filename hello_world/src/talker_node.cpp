#include <iostream>

#include "rclcpp/rclcpp.hpp"

#include "talker.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto talker_node = std::make_shared<TalkerNode>();

  rclcpp::spin(talker_node);

  rclcpp::shutdown();

  return 0;
}
