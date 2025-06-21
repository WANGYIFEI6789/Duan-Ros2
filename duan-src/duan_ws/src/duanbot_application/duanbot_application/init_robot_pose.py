from geometry_msgs.msg import PoseStamped
from nav2_simple_commander.robot_navigator import BasicNavigator
import rclpy

def main():
    rclpy.init()
    nav = BasicNavigator()  # 节点
    init_pose = PoseStamped()
    """
    frame_id 是 ROS 中坐标帧 Coordinate Frame 的标识符，用于指定数据所在的参考坐标系。
    "map" 是导航系统中固定的全局参考坐标系，通常表示整个地图的原点。
    这行代码表明初始位姿数据是相对于全局地图坐标系的
    设置时间戳为当前时刻，确保位姿数据的时效性。
    导航系统可能会忽略过时的位姿信息，因此时间戳很重要
    """
    init_pose.header.frame_id = "map"
    init_pose.header.stamp = nav.get_clock().now().to_msg()
    init_pose.pose.position.x = 0.0
    init_pose.pose.position.y = 0.0
    init_pose.pose.position.z = 0.0
    init_pose.pose.orientation.w = 1.0
    nav.setInitialPose(init_pose)
    nav.waitUntilNav2Active()  # 等待导航可用
    rclpy.spin(nav)
    rclpy.shutdown()