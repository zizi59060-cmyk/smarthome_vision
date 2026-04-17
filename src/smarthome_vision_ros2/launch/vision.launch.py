from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg_share = get_package_share_directory('smarthome_vision')
    config_path = os.path.join(pkg_share, 'config', 'vision.yaml')

    usb_cam_node = Node(
        package='usb_cam',
        executable='usb_cam_node_exe',
        name='usb_cam',
        output='screen',
        parameters=[{
            'video_device': '/dev/video0',
            'framerate': 30.0,
            'image_width': 640,
            'image_height': 480,
            'pixel_format': 'yuyv',
            'camera_frame_id': 'camera',
            'camera_name': 'default_cam',
            'io_method': 'mmap'
        }]
    )

    vision_node = Node(
        package='smarthome_vision',
        executable='vision_node',
        name='smarthome_vision_node',
        output='screen',
        parameters=[config_path],
    )

    return LaunchDescription([
        usb_cam_node,
        vision_node,
    ])