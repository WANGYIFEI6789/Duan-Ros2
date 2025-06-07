#include <QApplication>
#include <QLabel>
#include <QString>
#include <rclcpp/rclcpp.hpp>
#include <status_interfaces/msg/system_status.hpp>  // 自定义消息接口

using SystemStatus = status_interfaces::msg::SystemStatus;

class SysStatusDisplay : public rclcpp::Node{
private:
    rclcpp::Subscription<SystemStatus>::SharedPtr subscriber_;
    std::shared_ptr<QLabel> label_;
public:
    SysStatusDisplay() : Node("sys_status_display"){
        label_ = std::make_shared<QLabel>();
        // topic要和发布者保持一致 不然接收不到消息
        subscriber_ = this->create_subscription<SystemStatus>("sys_status", 10, [&](const SystemStatus::SharedPtr msg) -> void {
            label_->setText(get_qstr_from_msg(msg));
        });
        label_->setText(get_qstr_from_msg(
            std::make_shared<SystemStatus>()
        ));
        label_->show();
    }

    // # 组装消息
    //     msg = SystemStatus()
    //     msg.stamp = self.get_clock().now().to_msg()
    //     msg.host_name = platform.node()
    //     msg.cpu_percent = cpu_percent
    //     msg.memory_percent = memory_info.percent 
    //     msg.memory_total = memory_info.total / 1024 / 1024
    //     msg.memory_available = memory_info.available /1024 / 1024
    //     msg.net_sent = net_io_counters.bytes_sent / 1024 / 1024
    //     msg.net_recv = net_io_counters.bytes_recv / 1024 / 1024

    QString get_qstr_from_msg(const SystemStatus::SharedPtr msg){
        std::stringstream show_str;
        // 先输入一行进去    /t 让不同字段间保持统一的缩进  %表示普通字符 无特殊格式意义
        show_str << "=========端======状态可视化显示工具======菲～=========\n" << 
        "数 据 时 间:\t" << msg->stamp.sec << "\ts\n" << 
        "主 机 名 字:\t" << msg->host_name << "\t\n" <<
        "CPU 使用率:\t" << msg->cpu_percent << "\t%\n" <<
        "内存使用率:\t" << msg->memory_percent << "\t%\n" <<
        "内存总大小:\t" << msg->memory_total << "\tMB\n" <<
        "剩余有效内存:\t" << msg->memory_available << "\tMB\n" <<
        "网络发送量:\t" << msg->net_sent << "\tMB\n" <<
        "网络发送量:\t" << msg->net_recv << "\tMB\n"
        << "===========================================";
        return QString::fromStdString(show_str.str());
    }
};

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);
    // 这里不可以这样写 因为无论是spin放在前面  还是exec放在前面 都会将代码阻塞 达不到预期效果
    /* auto node = std::make_shared<SysStatusDisplay>();
    rclcpp::spin(node);
    // 执行应用  不断循环，阻塞代码
    app.exec(); */
    auto node = std::make_shared<SysStatusDisplay>();
    // 这里采用多线程去执行
    std::thread spin_thread([&]() -> void {
                            {
                                rclcpp::spin(node);
                            }
    });
    // 防止线程在上面等待执行  阻塞   应该使用detach
    spin_thread.detach();
    // 这里Qt就可以正常显示出来了
    app.exec();
    rclcpp::shutdown();
    return 0;
}