#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"  // 需要控制小海龟 所以需要这个头文件
#include <chrono>
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;  // 对秒数进行自动转换

class TurtleControlNode : public rclcpp::Node{
private:
    // 模板类的智能指针   发布者的智能指针  后续需要赋值
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    // 同理 订阅者
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
    // 目标位置 C++11 引入统一初始化方式{}
    double target_x_{1.0};
    double target_y_{1.0};
    // 比例系数
    double k_{1.0};
    // 最大速度  限制速度大小
    double max_speed_{3.0};
public:
    // explicit关键字 强制要求显式调用构造函数进行对象初始化
    explicit TurtleControlNode(const std::string& node_name) : Node(node_name){
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        // 订阅别人的话题 所以名字必须是这个话题的名字
        // 回调函数的参数就是收到的数据 参数：收到数据的共享指针
        // 如果非要写成类成员函数 就需要通过std::bind 转为函数对象
        subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, [&](const turtlesim::msg::Pose::SharedPtr pose){
            // TODO 
            // 根据当前位置 和 目标位置  计算出新的线速度和角速度
            // 终端下 可以通过ros2 interface show turtlesim/msg/Pose 查看接口定义
            // 1.获取当前的位置
            auto cur_x = pose->x;
            auto cur_y = pose->y;
            RCLCPP_INFO(get_logger(), "当前: x=%f,y=%f", cur_x, cur_y);
            // 2.计算当前小海龟位置跟目标位置之间的距离差和角度差
            auto distance = std::sqrt(
                (target_x_ - cur_x) * (target_x_ - cur_x) + 
                (target_y_ - cur_y) * (target_y_ - cur_y)
            );
            // atan2 = arctan  可以求出角度
            // 计算角度差
            auto angle = std::atan2((target_y_ - cur_y), (target_x_ - cur_x)) - pose->theta;
            // 3.控制策略
            auto msg = geometry_msgs::msg::Twist();

            // 距离 > 0.1  角度差 > 0.2 才作出控制 否则直接向前就好了
            if(distance > 0.1){
                if(fabs(angle) > 0.2){
                    // 角度差太大了 需要原地转一下
                    msg.angular.z = fabs(angle);
                }
                else{
                    // 否则直接走
                    msg.linear.x = k_ * distance;
                }
            }

            // 限制线速度最大值
            if(msg.linear.x > max_speed_){
                msg.linear.x = max_speed_;
            }
            
            // 再把控制的消息发布出去
            // 这里相当于订阅节点用来获取位置，发布节点通过计算 将控制消息发布出去
            publisher_->publish(msg);
        });
    }
};

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleControlNode>("turtle_control");
    // 运行节点
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}