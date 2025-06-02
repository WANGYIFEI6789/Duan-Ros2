import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/root/Code/duan/Topic/topic_2_ws/install/demo_python_topic'
