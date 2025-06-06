import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/duan/Code/Duan-Ros2/Topic/topic_practice_ws/install/status_publisher'
