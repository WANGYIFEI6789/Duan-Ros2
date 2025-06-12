import rclpy
from rclpy.node import Node
from tf2_ros import TransformBroadcaster # 静态坐标发布器 是一个类
from geometry_msgs.msg import TransformStamped # 消息接口
from tf_transformations import quaternion_from_euler # 欧拉角转四元素

class DynamicTFBroadcaster(Node):
    def __init__(self):
        super().__init__('dynamic_tf_broadcaster')
        # 需要通过静态坐标发布器去发布坐标
        self.dynamic_broadcaster_ = TransformBroadcaster(self)
        # 1秒发送100次
        self.timer_ = self.create_timer(0.01, self.publish_dynamic_tf)

    def publish_dynamic_tf(self):
        """
        发布动态TF 从 camera_link到bottle_link之间的坐标关系
        """
        transform = TransformStamped()
        transform.header.frame_id = 'camera_link'
        transform.child_frame_id = 'bottle_link'
        transform.header.stamp = self.get_clock().now().to_msg()
        
        transform.transform.translation.x = 0.2
        transform.transform.translation.y = 0.3
        transform.transform.translation.z = 0.5

        # 欧拉角转为四元素
        # 先转为弧度 再转为四元素
        # q为数组  q = x y z w
        q = quaternion_from_euler(0, 0, 0)
        # 旋转部分进行赋值
        transform.transform.rotation.x = q[0]
        transform.transform.rotation.y = q[1]
        transform.transform.rotation.z = q[2]
        transform.transform.rotation.w = q[3]

        # 将静态坐标关系发布出去
        self.dynamic_broadcaster_.sendTransform(transform)
        self.get_logger().info(f'发布动态TF:{transform}')

def main():
    rclpy.init()
    node = DynamicTFBroadcaster()
    rclpy.spin(node)
    rclpy.shutdown()