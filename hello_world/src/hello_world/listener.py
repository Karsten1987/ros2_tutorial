import sys

import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class Listener(Node):

    def __init__(self):
        super().__init__('listener_py')
        self.sub = self.create_subscription(String, 'hello_world_topic', self.chatter_callback)

    def chatter_callback(self, msg):
        self.get_logger().info('I heard: [%s]' % msg.data)


def main(args=None):
    if args is None:
        args = sys.argv

    rclpy.init(args=args)

    node = Listener()
    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
