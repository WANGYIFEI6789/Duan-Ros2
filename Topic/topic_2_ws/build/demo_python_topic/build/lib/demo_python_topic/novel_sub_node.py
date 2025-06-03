import espeakng
import rclpy
from rclpy.node import Node 
# from example_interfaces.msg import String
from std_msgs.msg import String
from queue import Queue
import threading
import time

class NovelSubNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.get_logger().info(f'{node_name}, 启动!')
        self.novels_queue_ = Queue()
        # 创建一个订阅者
        # 这里topic的名字  发布者 订阅者必须保持一致
        # 发布者只需要发布消息就可以了，订阅者必须要有回调，告诉自己有数据了
        self.novel_subscriber_ = self.create_subscription(String, "novel", self.novel_callback, 10)
        self.speech_thread_ = threading.Thread(target=self.speak_thread)
        # 线程启动 python里面的线程不会自己启动
        self.speech_thread_.start()
    
    # 这个message就是发布者发送的消息 ros2已经在内部帮我们处理好了  
    def novel_callback(self, message):
        self.novels_queue_.put(message.data)
        self.get_logger().info(f'收到消息: {message.data}')
        
    
    def speak_thread(self):
        # 生成一个对象
        speaker = espeakng.Speaker()
        # 设置一下属性 zh表示中文
        speaker.voice = 'zh-yue'
        
        while rclpy.ok(): # 检测当前ros上下文是否ok
            if self.novels_queue_.qsize() > 0:
                text = self.novels_queue_.get()
                # 打印一下文字 不要一声不吭就朗读
                self.get_logger().info(f'朗读: {text}')
                speaker.say(text)
                # 说完才能说下一句
                speaker.wait()
            else:
                # 没数据的时候  要让当前线程休眠
                # 一直让线程while循环 和 适当休眠 对cpu的功耗是不一样的
                time.sleep(1)
        
def main():
    rclpy.init()
    node = NovelSubNode('novel_sub')
    rclpy.spin(node)
    rclpy.shutdown()