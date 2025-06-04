#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"  // 需要控制小海龟 所以需要这个头文件
#include <chrono>

using namespace std::chrono_literals;  // 对秒数进行自动转换

class TurtleCircleNode : public rclcpp::Node{
private:
    // 定时器  持续去发送信息
    rclcpp::TimerBase::SharedPtr timer_;
    // 模板类的智能指针   发布者的智能指针  后续需要赋值
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
public:
    // explicit关键字 强制要求显式调用构造函数进行对象初始化
    explicit TurtleCircleNode(const std::string& node_name) : Node(node_name){
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        // 我这里采用匿名函数作为回调函数
        timer_ = this->create_wall_timer(1000ms, [&](){
            // 创建消息
            auto msg = geometry_msgs::msg::Twist();
            // 设置消息内容 线速度
            msg.linear.x = 1.0;
            msg.angular.z = 0.5;
            // 发布消息
            publisher_->publish(msg);
        });
    }
};

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleCircleNode>("turtle_circle");
    // 运行节点
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}