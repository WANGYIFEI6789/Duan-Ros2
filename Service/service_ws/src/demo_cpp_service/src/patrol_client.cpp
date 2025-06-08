#include "rclcpp/rclcpp.hpp"
#include "ser_interfaces/srv/patrol.hpp"
#include <chrono>
#include <ctime> // 产生随机数
#include "rcl_interfaces/msg/parameter.hpp"  // 要做到实时修改另一个参数，就需要包括以下几个头文件
#include "rcl_interfaces/msg/parameter_value.hpp"
#include "rcl_interfaces/msg/parameter_type.hpp"
#include "rcl_interfaces/srv/set_parameters.hpp"

using SetP = rcl_interfaces::srv::SetParameters;
using Patrol = ser_interfaces::srv::Patrol;
using namespace std::chrono_literals;  // 使用10s 100ms 表示时间

class PatrolClient : public rclcpp::Node{
public:
    PatrolClient() : Node("turtle_controller"){
        patrol_client_ = this->create_client<Patrol>("patrol");
        timer_ = this->create_wall_timer(5s, [&]() -> void{
            // 1.检测服务端是否上线
            while(!this->patrol_client_->wait_for_service(1s)){
                if(!rclcpp::ok()){
                    RCLCPP_ERROR(this->get_logger(), "等待服务上线过程中，rclcpp挂了，我退下了");
                    return;
                }
                RCLCPP_INFO(this->get_logger(), "等待服务上线中......");
                // 在这里初始化一下随机数种子
                srand(time(NULL));
            }
            // 2.构造请求对象
            auto request = std::make_shared<Patrol::Request>();
            // 需要产生随机数
            request->target_x = rand() % 15;
            request->target_y = rand() % 15;
            RCLCPP_INFO(this->get_logger(), "已准备好目标点%f, %f", request->target_x, request->target_y);
            // 3.发送请求
            // 异步发送
            this->patrol_client_->async_send_request(request, [&]
            (rclcpp::Client<Patrol>::SharedFuture result_future) -> void{
                auto response = result_future.get();
                if(response->result == Patrol::Response::SUCCESS){
                    RCLCPP_INFO(this->get_logger(), "请求巡逻目标点成功");
                }
                if(response->result == Patrol::Response::FAIL){
                    RCLCPP_INFO(this->get_logger(), "请求巡逻目标点失败");
                }
            });
        });
    }

    /*
    创建客户端发送请求，返回结果
    */
    SetP::Response::SharedPtr call_set_parameters(rcl_interfaces::msg::Parameter &param){
        auto param_client = this->create_client<SetP>("/turtle_control/set_parameters");
        // 1.检测服务端是否上线
        while(!param_client->wait_for_service(1s)){
            if(!rclcpp::ok()){
                RCLCPP_ERROR(this->get_logger(), "等待服务上线过程中，rclcpp挂了，我退下了");
                return nullptr;
            }
            RCLCPP_INFO(this->get_logger(), "等待服务上线中......");
        }
        // 2.构造请求对象
        auto request = std::make_shared<SetP::Request>();
        request->parameters.push_back(param);
        // 3.发送请求
        // 异步发送
        auto future = param_client->async_send_request(request);
        rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);
        auto response = future.get();
        return response;
    }

    /*
    更新参数k
    */
    void update_server_param_k(double k){
        // 1.创建参数对象
        auto param = rcl_interfaces::msg::Parameter();
        param.name = "k";
        // 2.创建参数值
        auto param_value = rcl_interfaces::msg::ParameterValue();
        param_value.type = rcl_interfaces::msg::ParameterType::PARAMETER_DOUBLE;
        param_value.double_value = k;
        param.value = param_value;
        // 3.请求更新参数并处理
        auto response = this->call_set_parameters(param);
        if(response == NULL){
            RCLCPP_INFO(this->get_logger(), "参数更新失败");
            return;
        }
        for(auto result : response->results){
            if(result.successful == false){
                RCLCPP_INFO(this->get_logger(), "参数更新失败：%s", result.reason.c_str());

            }
            else{
                RCLCPP_INFO(this->get_logger(), "参数更新成功");
            }
        }
    }

private:
    // 定时器  需要定时给一个位置 和 请求服务
    rclcpp::TimerBase::SharedPtr timer_;
    // 创建一个客户端
    rclcpp::Client<Patrol>::SharedPtr patrol_client_;
};

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PatrolClient>();
    node->update_server_param_k(4.0);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}