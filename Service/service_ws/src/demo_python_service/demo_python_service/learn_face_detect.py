import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory # 获取 ROS2 功能包的共享目录路径
import os

def main():
    # 获取图片真实路径
    default_image_path = os.path.join(get_package_share_directory('demo_python_service'), 'resource/default.jpg')
    print(f"图片真实路径:{default_image_path}")
    # 使用cv2来加载图片
    image = cv2.imread(default_image_path)
    # 检测人脸
    face_locations = face_recognition.face_locations(image, number_of_times_to_upsample=1, model='hog')
    # 绘制人脸框
    for top, right, bottom, left in face_locations:
        # 给左上角 右下角  框框颜色  宽度
        cv2.rectangle(image, (left, top), (right, bottom), (0, 255, 0), 4)
    
    # 保持宽高比，根据屏幕大小自动计算合适的尺寸
    max_width = 800
    max_height = 600
    # 计算宽高比
    height, width = image.shape[:2]
    ratio = min(max_width/width, max_height/height)
    # 计算新尺寸
    new_width = int(width * ratio)
    new_height = int(height * ratio)
    dim = (new_width, new_height)
    # 执行缩放
    image = cv2.resize(image, dim, interpolation=cv2.INTER_AREA)

    # 结果显示
    cv2.imshow('Face Detect Result', image)
    cv2.waitKey(0)