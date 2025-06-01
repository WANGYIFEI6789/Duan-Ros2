# 目录介绍
Image文件夹存放的是后续在讲解中会用到的图片  
Node文件夹用来存放学习基础知识时编写的代码  
Topic文件夹是在学习topic通信时编写的代码  
duan-src是存放项目代码的文件夹
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
