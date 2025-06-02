#include <rclcpp/rclcpp.hpp>
#include <cpp-httplib/httplib.h>  // 下载相关的头文件
#include <std_msgs/msg/string.hpp>  // 消息接口的类型
#include <queue>

class NovelPubNode : public rclcpp::Node{
private:
    // 声明话题发布者指针
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr novel_publisher_;
    // 声明定时器指针
    rclcpp::TimerBase::SharedPtr timer_;
    // 创建一个队列，用来存放下载小说的每一行
    std::queue<std::string> mq_;
    void timer_callback(){
        std::string line;
        // 创建topic发送的消息对象
        std_msgs::msg::String message;
        if(mq_.size() > 0){
            // 发布消息
            line = mq_.front(); 
            mq_.pop();
            message.data = line;
            // 把message放入发布者中
            novel_publisher_->publish(message);
            RCLCPP_INFO(this->get_logger(), "发布了: '%s'", message.data.c_str());
        }
    }
public:
    NovelPubNode(const std::string& node_name) : Node(node_name){
        RCLCPP_INFO(this->get_logger(), "%s, 启动！", node_name.c_str());
        // 创建发布者
        novel_publisher_ = this->create_publisher<std_msgs::msg::String>("novel", 10);
        // 创建定时器，5s为周期，定时发布
        timer_ = this->create_wall_timer(std::chrono::milliseconds(5000), std::bind(&NovelPubNode::timer_callback, this));
    }

    // 从服务器上下载小说内容
    void download(const std::string& host, const std::string& path){
        httplib::Client client(host);
        auto response = client.Get(path);
        if(response && response->status == 200){
            std::string text = response->body;
            std::cout << "下载完成：" << path << ":" << "下载大小：" << text.size() << std::endl;
            // 按行分 放入队列
            std::istringstream iss(text);
            std::string line;
            while(std::getline(iss, line)){
                mq_.push(line);
            }
        }
    }
};

int main(int argc, char** argv){
    // 初始化rclcpp库
    rclcpp::init(argc, argv);
    // 创建节点实例
    auto node = std::make_shared<NovelPubNode>("novel_pub");
    // 下载小说
    node->download("http://0.0.0.0:8000", "/novel.txt");
    // 使节点进入自选状态，处理回调等
    rclcpp::spin(node);
    // 关闭rclcpp库
    rclcpp::shutdown(); 
    return 0;
}