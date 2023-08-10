from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='simple_ros2',
            namespace='simple_ros2',
            executable='simple_ros2',
            name='simple_ros2',
            arguments=["--ros-args", "--log-level", "info"],
            output="screen",
            respawn=True,
            respawn_delay=3,
        )
    ])
