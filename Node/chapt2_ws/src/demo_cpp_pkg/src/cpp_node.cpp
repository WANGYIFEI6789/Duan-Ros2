#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv){
    // rclcpp进行初始化
    rclcpp::init(argc, argv);
    // 创建节点
    auto node = std::make_shared<rclcpp::Node>("duan_node");
    // 打印日志
    RCLCPP_INFO(node->get_logger(), "你好,我是duan~");
    // 启动节点 & 不断循环
    rclcpp::spin(node);
    // 关闭 清理资源
    rclcpp::shutdown();
    return 0;
}