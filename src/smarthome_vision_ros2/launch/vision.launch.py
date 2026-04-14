from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    pkg_share = get_package_share_directory('smarthome_vision')
    config_path = os.path.join(pkg_share, 'config', 'vision.yaml')

    return LaunchDescription([
        Node(
            package='smarthome_vision',
            executable='vision_node',
            # 修改这里：确保这里的 name 与 vision.yaml 中的开头一致
            name='smarthome_vision_node', 
            output='screen',
            parameters=[config_path],
        )
    ])