import launch
import launch.event_handlers
import launch.launch_description_sources
import launch_ros # ros2启动系统的核心模块
from ament_index_python.packages import get_package_share_directory # 获取功能包的安装路径 安装是通过CMakeLists
import os

import launch_ros.parameter_descriptions # 用于处理参数值的特殊类型

def generate_launch_description():
    # 获取功能包share路径
    urdf_package_path = get_package_share_directory('duanbot_description')
    # 机器人模型文件
    default_xacro_path = os.path.join(urdf_package_path, 'urdf', 'duanbot/duanbot.urdf.xacro')
    # default_rviz_config_path = os.path.join(urdf_package_path, 'config', 'display_robot_model.rviz')
    # 仿真世界文件
    default_gazebo_world_path = os.path.join(urdf_package_path, 'world', 'custom_room.world')
    # 声明一个urdf目录的参数 方便修改
    action_declare_arg_mode_path = launch.actions.DeclareLaunchArgument(
        name='model', default_value=str(default_xacro_path), description='加载的模型文件路径'
    )

    # 通过文件路径获取内容并转换为参数值对象，以供传入 robot_state_publisher
    substitutions_command_result = launch.substitutions.Command(['xacro ', launch.substitutions.LaunchConfiguration('model')])
    robot_description_value = launch_ros.parameter_descriptions.ParameterValue(substitutions_command_result, value_type=str)

    # 可视化和控制机器人
    """
    1.从 robot_description 参数获取完整的 URDF 模型
    2.监听 /joint_states 话题（由关节控制器或模拟器发布）
    3.根据接收到的关节位置（如 shoulder_pan_joint=0.5 弧度）
    4.计算所有连杆和关节的位置和姿态
    5.通过 /tf 和 /tf_static 话题发布 TF 变换树
    """
    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description':robot_description_value}]
    )

    # 启动gazebo
    action_launch_gazebo = launch.actions.IncludeLaunchDescription(
        launch.launch_description_sources.PythonLaunchDescriptionSource(
            [get_package_share_directory('gazebo_ros'),'/launch','/gazebo.launch.py']
        ),
        launch_arguments=[('world', default_gazebo_world_path),('verbose','true')]
    )

    # 加载机器人到gazebo
    action_spawn_entity = launch_ros.actions.Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic','/robot_description','-entity','duanbot']
    )

    action_load_joint_state_controller = launch.actions.ExecuteProcess(
        cmd='ros2 control load_controller duanbot_joint_state_broadcaster --set-state active'.split(' '),
        output='screen'
    )

    action_load_effort_controller = launch.actions.ExecuteProcess(
        cmd='ros2 control load_controller duanbot_effort_controller --set-state active'.split(' '),
        output='screen'
    )

    action_load_diff_driver_controller = launch.actions.ExecuteProcess(
        cmd='ros2 control load_controller duanbot_diff_drive_controller --set-state active'.split(' '),
        output='screen'
    )

    return launch.LaunchDescription([
        action_declare_arg_mode_path,
        action_robot_state_publisher,
        action_launch_gazebo,
        action_spawn_entity,
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=action_spawn_entity,
                on_exit=[action_load_joint_state_controller]
            )
        ),
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=action_load_joint_state_controller,
                on_exit=[action_load_diff_driver_controller]
            )
        ),
    ])