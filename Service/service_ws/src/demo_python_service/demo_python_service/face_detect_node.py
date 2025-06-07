import rclpy
from rclpy.node import Node
from ser_interfaces.srv import FaceDetector
import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory # 获取 ROS2 功能包的共享目录路径
import os
from cv_bridge import CvBridge  # 转图像格式的库
import time

class FaceDetectNode(Node):
    def __init__(self):
        super().__init__('face_detect_node')
        self.service_ = self.create_service(FaceDetector, 'face_detect', self.detect_face_callback)
        self.bridge = CvBridge()
        self.number_of_times_to_upsample = 1 
        self.model = 'hog'
        self.default_image_path = os.path.join(get_package_share_directory
        ('demo_python_service'), 'resource/default.jpg')
        self.get_logger().info("人脸检测服务已经启动!")

    def detect_face_callback(self, request, response):
        # 考虑程序的健壮性 if else一下
        if request.image.data:
            cv_image = self.bridge.imgmsg_to_cv2(request.image)
        else:
            cv_image = cv2.imread(self.default_image_path)
            self.get_logger().info(f"传入图像为空，使用默认图像！")
        # cv_image已经是一个opencv格式的图像了
        start_time = time.time()
        self.get_logger().info(f"加载完图像，开始识别！")
        face_locations = face_recognition.face_locations(cv_image, 
            number_of_times_to_upsample=self.number_of_times_to_upsample, model=self.model)
        response.use_time = time.time() - start_time
        response.number = len(face_locations)

        for top, right, bottom, left in face_locations:
            response.top.append(right)
            response.right.append(right)
            response.bottom.append(bottom)
            response.left.append(left)

        return response  # 必须返回response

def main():
    rclpy.init()
    node = FaceDetectNode()
    rclpy.spin(node)
    rclpy.shutdown()