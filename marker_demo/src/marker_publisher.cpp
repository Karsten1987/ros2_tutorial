#include <cstdio>

#include "geometry_msgs/msg/transform.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"

using namespace std::chrono_literals;

class MarkerPublisher : public rclcpp::Node
{
public:
  MarkerPublisher(std::string node_name):
    rclcpp::Node(node_name)
  {
    pub_ = this->create_publisher<visualization_msgs::msg::Marker>("marker");
    timer_ = this->create_wall_timer(100ms, std::bind(&MarkerPublisher::publish_message, this));

    msg_ = std::make_shared<visualization_msgs::msg::Marker>();
    msg_->header = std_msgs::msg::Header();
    msg_->id = 1;
    msg_->type = 2; // Sphere
    msg_->color.r = 1;
    msg_->color.a = 1;
    msg_->header.frame_id = "marker_frame";
    msg_->scale.x = 1;
    msg_->scale.y = 1;
    msg_->scale.z = 1;
  }

  void publish_message() {
    msg_->header.stamp = rclcpp::Clock().now();
    static float tick = 0.0f;
    tick += 0.1;
    msg_->pose.position.x = cos(tick);
    msg_->pose.position.y = sin(tick);

    pub_->publish(msg_);
  }

private:
  std::shared_ptr<visualization_msgs::msg::Marker> msg_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

class TFPublisher : public rclcpp::Node
{
public:
  TFPublisher():
    rclcpp::Node("MarkerTFPublisher")
  {}

  void init()
  {
    tf_pub_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(shared_from_this());
    transform_msg_ = std::make_shared<geometry_msgs::msg::TransformStamped>();
    transform_msg_->header.stamp = rclcpp::Clock().now();
    transform_msg_->header.frame_id = "base_frame";
    transform_msg_->child_frame_id = "marker_frame";
    transform_msg_->transform.translation.x = 1.0;
    transform_msg_->transform.rotation.w = 1.0;
    timer_ = this->create_wall_timer(100ms, [&]() {
        tf_pub_->sendTransform(*transform_msg_);
      });
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_pub_;
  std::shared_ptr<geometry_msgs::msg::TransformStamped> transform_msg_;
};

int main(int argc, char ** argv)
{
  std::string node_name = "MarkerPublisher";
  if (argc > 1) {
    node_name = argv[1];
  }
  printf("starting %s node\n", node_name.c_str());

  rclcpp::init(argc, argv);

  auto marker_node = std::make_shared<MarkerPublisher>(node_name);
  auto tf_node = std::make_shared<TFPublisher>();
  tf_node->init();

  auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
  executor->add_node(marker_node);
  executor->add_node(tf_node);
  executor->spin();

  return 0;
}
