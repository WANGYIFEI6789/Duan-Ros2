import rclpy
from rclpy.node import Node
from ser_interfaces.srv import FaceDetector
import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory # 获取 ROS2 功能包的共享目录路径
import os
from cv_bridge import CvBridge  # 转图像格式的库
import time

class FaceDetectClientNode(Node):
    def __init__(self):
        super().__init__('face_detect_client_node')
        self.bridge = CvBridge()
        self.default_image_path = os.path.join(get_package_share_directory
        ('demo_python_service'), 'resource/test1.jpg')
        self.get_logger().info("人脸检测客户端已经启动!")
        self.client = self.create_client(FaceDetector, 'face_detect')
        self.image = cv2.imread(self.default_image_path)

    def send_request(self):
        # 1.判断服务端是否在线 这个服务有没有上线
        # 等待超时时间
        while self.client.wait_for_service(timeout_sec=1.0) is False:
            self.get_logger().info('等待服务端上线')
        # 2.构造Request
        request = FaceDetector.Request()
        request.image = self.bridge.cv2_to_imgmsg(self.image)
        # 3.发送请求并等待处理完成
        # 创建服务请求并异步获取结果
        # 现在future中并没有包含response result  所以这个单词也有未来的意思
        # 需要等待服务端处理完成才会把结果放在future中
        future = self.client.call_async(request)
        # # 目前程序是单线程，所以程序会死睡在这里
        # # 造成当前线程无法再来接收来自服务端的返回
        # # 导致永远无法完成
        # while not future.done():
        #     time.sleep(1.0)  # 休眠当前线程

        # ros2对这个问题有处理
        # 在后台边去接收结果  边去等待
        # rclpy.spin_until_future_complete(self, future)  # 等待服务端返回响应
        # 另一种写法 防止spin阻塞
        def result_callback(result_future):
            response = future.result() # 获取响应
            self.get_logger().info(f'接收到响应，共检测到有{response.number}张人脸，耗时{response.use_time}s')
            self.show_response(response)

        future.add_done_callback(
            result_callback
        )

    def show_response(self, response):
        for i in range(response.number):
            top = response.top[i]
            right = response.right[i]
            bottom = response.bottom[i]
            left = response.left[i]
            cv2.rectangle(self.image, (left, top), (right, bottom), (0, 255, 0), 4)
        cv2.imshow('Face Detect Result', self.image)
        cv2.waitKey(0) # 也是阻塞的 会导致spin无法正常运行
        # 但是这里是只发送一次请求，所以不影响 最终卡在这里也没关系
        # 但是在以后的代码中，如果需要发送多次请求，就需要注意一下

def main():
    rclpy.init()
    node = FaceDetectClientNode()
    node.send_request()
    rclpy.spin(node)
    rclpy.shutdown()