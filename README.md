# 目录介绍
Image文件夹存放的是后续在讲解中会用到的图片  
Node文件夹用来存放学习基础知识时编写的代码  
Topic文件夹是在学习topic通信时编写的代码  
duan-src是存放项目代码的文件夹  
Cpp-YiFei存放C++新特性示例代码
# 运行小海龟
我们学习每个编程语言的时候，第一次学都是会去打印hello world  
同理，学习ros2的时候会去打印小海龟

在终端中运行
ros2是安装好ros2后会提供的命令
run是运行
turtlesim是功能包的名字
turtlesim_node是可执行文件的名字
```bash
ros2 run turtlesim turtlesim_node
``` 
使用键盘控制小海龟
```bash
ros2 run turtlesim turtle_teleop_key
```
tips:不是通过点击小海龟界面来使它移动
再打开一个终端，运行另一个可执行程序
在新打开的终端输入键盘按键来控制，相当于是两个节点进行通信
效果：
![小海龟移动](./Image/1.png)  
为什么会在一个终端输入指令，另一个终端会做出反应呢？  
可以再打开一个终端，输入rqt，点击回车，会出现这样的界面
![topic通信](./Image/2.png)
这里是两个节点，左边的节点表示小海龟模拟器的节点，右边的节点表示键盘的按键，看箭头可以发现右边节点向左边节点发送了一个topic提供数据，然后小海龟模拟器会做出一个反馈（响应）
# CMakeList编写示例
写一段CMakeLists的编写 默认情况下CMake会自动寻找系统中已安装的C++编译器
```CMakeLists
# cmake需要的最小版本
cmake_minimum_required(VERSION 3.8)
# 配置工程的名字
project(HelloWorld)
# 添加可执行文件 第一个参数是可执行文件的名字 第二个参数是cpp文件的名字
add_execuatable(learn_cmake hello_world.cpp)
```

再编写一段实现第一个节点cpp文件的CMakeLists
```CMakeList
cmake_minimum_required(VERSION 3.8)
project(ros2_cpp)
add_executable(ros2_cpp_node ros2_cpp_node.cpp)

# 查找rclcpp头文件和库文件的路径
find_package(rclcpp REQUIRED)
# 给可执行文件包含头文件
target_include_directories(ros2_cpp_node PUBLIC ${rclcpp_INCLUDE_DIRS})
# 给可执行文件链接库文件
target_link_libraries(ros2_cpp_node ${rclcpp_LIBRARIES})
```
查看正在运行节点列表
```bash
ros2 node list
```
查看具体节点的信息
```bash
ros2 node info /duan_node
```
# 使用功能包组织C++节点
ros2 pkg create 是ros2提供的用于创建功能包的命令  
demo_cpp_pkg 为要创建的功能包的名称(相当于是一个文件夹)  
--build-type ament_cmake 指定功能包的构建类型为ament_cmake  
在ros2中ament是构建系统，ament_cmake是基于CMake的构建方式  
--license Apache-2.0 指定功能包所采用的开源许可证为Apache-2.0  
这表明功能包代码遵循 Apache - 2.0 协议的相关规定，包括版权声明、许可使用条件等
```bash
ros2 pkg create demo_cpp_pkg --build-type ament_cmake --license Apache-2.0
```
通过上述命令创建功能包之后，会在功能包下面自动生成一个CMakeLists.txt文件，在编写完Cpp代码后，需要去里面手动修改一下，一般情况下添加如下代码并修改可执行文件的名称即可
```CMakeLists
find_package(rclcpp REQUIRED)
add_executable(cpp_node src/cpp_node.cpp)
# target_include_directories(cpp_node PUBLIC ${rclcpp_INCLUDE_DIRS})
# target_link_libraries(cpp_node ${rclcpp_LIBRARIES})
# 可以替换上述两行的方式  可以通过ament_cmake的构建方式进行简写
ament_target_dependencies(cpp_node rclcpp)
```
也可以在功能包(demo_cpp_pkg)上一级目录下，通过colcon去构建  
![目录层级](./Image/3.png)
```bash
colcon build
```
colcon是ros2中推荐使用的构建工具，用于编译和管理工作空间中的多个功能包
tips：ldd可以查看某个可执行文件依赖哪些库
```bash
ldd cpp_node
```
在通过功能包实现节点之后，通过执行命令
```bash
ros2 run demo_cpp_pkg cpp_node
```
上述命令生成的可执行文件会在build目录下对应的功能包中
会发现出现问题 Package 'demo_cpp_pkg' not found  原因为：没有修改环境变量，需要执行下述命令通过脚本(export)帮我们修改环境变量
```bash
source install/setup.bash
```
再次执行会发现已经会报错 No executable found 是因为没有找到可执行文件 需要再去对应的CMakeLists.txt中添加如下代码 通过install命令 将可执行文件拷贝到install目录对应的功能包目录下
```CMakeList
install(TARGETS cpp_node
  DESTINATION lib/${PROJECT_NAME}
)
```
在使用功能包组织节点的时候，会自动生成一个package.xml文件，用于描述功能包的基本信息、依赖关系和构建要求，最好能进行一个声明
最后，一个功能包的完整结构如下：
![功能包完整结构](./Image/4.png)
# WorkSpace
在工作空间下如果有多个功能包，但目前执行构建一个功能包，colcon会一次性全部构建完这个时候要怎么办呢？  
功能包构建产生的临时文件和功能包在同一目录下，此时如果想新增功能包就会很混乱，这个时候又要怎么办呢？  
所以接下来会介绍多功能包的最佳实践
一个完整的机器人项目往往由多个不同的功能模块组成，所以就需要对多个功能包进行组合  
ROS2开发者约定了Workspace--即工作空间这一概念  
首先创建双重目录 -p 递归创建
```bash
mkdir -p chapt2_ws/src
```
将之前的功能包拷贝到工作空间下
```bash
mv demo_cpp_pkg/ chapt2_ws/src/
```
删除之前的临时文件
```bash
rm -rf build/ install/ log/
```
然后就可以cd到chapt2_ws目录下 执行colcon build
```bash
cd chapt2_ws
colcon build
```
可以通过--help 以及 grep命令过滤查看colcon build都有什么使用方法
```bash
colcon build --help | grep select
```
只选用一个功能包
```bash
colcon build --packages-select demo_cpp_pkg
```
同时还可以在Workspace中决定功能包的构建顺序  
可以在python功能包的package.xml中加上<depend>demo_cpp_pkg</depend>
```xml
<depend>rclpy</depend>
<depend>demo_cpp_pkg</depend>
```
# 用得到的C++新特性
示例都在Cpp-YiFei文件夹下  
auto 自动类型推导  
make_shared 创建智能指针  
Lambda 匿名函数  
functional 函数包装器：在C++中有以下几种函数：  
1.自由函数（就是在外部封装一个函数，需要的时候去调用即可）
2.成员函数
3.Lambda函数  
通过函数包装器可以实现统一的调用方法  
多线程与回调函数示例  
这里以下载小说为例，线程1下载(第一章) 线程1统计数字(第一章内容)  
线程2下载(第二章) 线程2统计数字(第二章内容)  
线程3下载(第三章) 线程3统计数字(第三章内容)  
回调函数，回调回调，回头再调  
这里先去下载一个httplib，下载存放位置为Cpp-YiFei/include/
A C++11 single-file header-only cross platform HTTP/HTTPS library  
意思是说  单一头文件就支持HTTP/HTTPS跨平台，为了支持下载功能
```bash
git clone https://gitee.com/ohhuo/cpp-httplib.git
```
在对应的CMakeLists.txt中包含incluide目录，完整的CMakeList如下
```CMakeList
cmake_minimum_required(VERSION 3.8)
project(CppNew)

# 包含include头文件目录
include_directories(include)
add_executable(learn_auto learn_auto.cpp)
add_executable(learn_shared_ptr learn_shared_ptr.cpp)
add_executable(learn_lambda learn_lambda.cpp)
add_executable(learn_functional learn_functional.cpp)
add_executable(learn_thread learn_thread.cpp)
```
使用到了std::bind   std::thread
```C++
// 用法：第一个为可执行的函数(如果为类成员函数，需要再后面再传一个this指针)
// 后续的参数为占位符，代表需要用到几个参数，std::placeholder::_1,...
std::bind(callable, agr1, arg2, ...);
// callable为函数对象，后续的参数为该函数对象需要使用到的参数
std::thread(callable, arg1, arg2, ...);
// 避免线程阻塞，所以需要使用线程分离
thread::detach();
```
# 话题通信介绍
在话题通信这里会有四个关键点：发布者  订阅者  话题名称  话题类型  
举个例子--海龟模拟器话题  
![海龟模拟器话题](./Image/5.png)  
可以看到对应的话题名称：话题类型  
这里是一些常用的命令，可以去看话题名称，话题类型，对应的数据内容等  
```bash
# 查看节点订阅了哪些topic 发布了哪些topic
ros2 run node info /turtlesim
# 查看某个话题的数据内容
ros2 topic echo /turtle1/pose
# 查看一个话题信息 包括消息类型、发布者数量、订阅者数量等等
ros2 topic info /turtle/cmd_vel -v
# 查看某个消息接口的定义
ros2 interface show geometry_msgs/msg/Twist
# 发布话题
ros2 topic pub /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 1.0}}"
```
```bash
# 启动小海龟
ros2 run turtlesim turtlesim_node
# 发布一个话题
ros2 topic pub /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 1.0}}"
# 小海龟订阅了这个话题，所以会执行相关的命令
```
效果如下：  
![发布topic](./Image/6.png)  
接下来实现一个小demo，下载小说并通过话题间隔5s发布一行  
核心问题：  
问题1：怎么下载小说？request  
问题2：怎么发布？确定名字和接口  
问题3：怎么间隔5s发布？Timer定时器  
代码放在Topic文件夹下，首先创建一个工作空间  
```bash
mkdir -p topic_ws/src
# 在src下创建功能包
cd topic_ws/src/
# 添加依赖 & 添加证书
# 需要依赖rclcpp 因为发送的为string类型 这个接口类型在example_interfaces中
ros2 pkg create demo_cpp_topic --build-type ament_cmake --dependencies rclcpp example_interfaces --license Apache-2.0
# 然后回到topic_ws目录下
cd ..
# 执行colcon build 这样一个完整的工作目录就有了
colcon build
```
```bash
# 查看example_interfaces接口类型
ros2 interface list | grep example_interfaces
# 查看example_interfaces/msg/String接口内容
ros2 interface show example_interfaces/msg/String
```
启动http服务
```bash
# 在最外层的Topic目录下启动
# 小说也放在Topic目录下 novel novel1 novel2 novel3
python3 -m http.server
```
```C++
// 小说发布节点
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
```
对应的CMakeLists.txt
```CMakeLists
cmake_minimum_required(VERSION 3.8)
project(demo_cpp_topic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
include_directories(include/demo_cpp_topic)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)


add_executable(novel_pub_node src/novel_pub_node.cc)
ament_target_dependencies(novel_pub_node rclcpp std_msgs)

install(TARGETS novel_pub_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
```
对应的package.xml
```xml
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
  <name>demo_cpp_topic</name>
  <version>0.0.0</version>
  <description>TODO: Package description</description>
  <maintainer email="15829054506@163.com">root</maintainer>
  <license>Apache-2.0</license>

  <buildtool_depend>ament_cmake</buildtool_depend>

  <depend>rclcpp</depend>
  <depend>example_interfaces</depend>
  <depend>std_msgs</depend>

  <test_depend>ament_lint_auto</test_depend>
  <test_depend>ament_lint_common</test_depend>

  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>
```
```bash
# 构建  在topic_ws目录下
colcon build
# 查看是否有这个topic的信息
ros2 topic list
# 查看topic发出的信息
ros2 topic echo /novel
```
基于上述的小demo继续开发  
订阅小说并逐行朗读  
核心问题：  
问题1：怎么订阅  
问题2：用什么来朗读文本？  Espeak  
问题3：小说来的快，读的太慢怎么办？队列  
这里的订阅节点使用python去编写，因为我想通过espeakng库让小说读起来
```bash
sudo apt install python3-pip -y
pip3 install espeakng
sudo apt install espeak-ng
```
我将订阅节点放在topic_2_ws/src/目录下  
```bash
ros2 pkg create demo_python_topic --build-type ament_python --dependencies rclpy example_interfaces --license Apache-2.0
# 接下来在Topic/topic_2_ws/src/demo_python_topic/ 创建novel_sub_node.py
```
