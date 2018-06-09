#include <cstdio>

#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"

using namespace std::chrono_literals;

class MarkerSubscriber : public rclcpp::Node
{
public:
  MarkerSubscriber(std::string node_name):
    rclcpp::Node(node_name)
  {
    sub_ = this->create_subscription<visualization_msgs::msg::Marker>(
        "marker",
        [](std::shared_ptr<visualization_msgs::msg::Marker> msg) -> void {
          printf("Received marker at position x: %f and y: %f\n",
              msg->pose.position.x,
              msg->pose.position.y);
          });
  }

private:
  rclcpp::Subscription<visualization_msgs::msg::Marker>::SharedPtr sub_;
};

int main(int argc, char ** argv)
{
  std::string node_name = "MarkerSubscriber";
  if (argc > 1) {
    node_name = argv[1];
  }
  printf("starting %s node\n", node_name.c_str());

  rclcpp::init(argc, argv);

  auto marker_node = std::make_shared<MarkerSubscriber>(node_name);

  rclcpp::spin(marker_node);

  return 0;
}
