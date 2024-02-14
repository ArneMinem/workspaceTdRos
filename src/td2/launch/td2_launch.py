import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

print("Lancement Q15")

# Fonction appelé par ros2 launch pour avoir la liste des nodes à lancer
def generate_launch_description():
        config = os.path.join(
                get_package_share_directory('td2'),
                'config', # repertoire
                'td2.yaml'
        )
        nodeS = Node(
                package='td2', # nom du package
                namespace='bat1',
                executable='NodeSimu', # nom de l'executable
                name='nodeSimu', # nom du node lors du lancement
                parameters=[config]
        )
        nodeC = Node(
                package='td2', # nom du package
                namespace='bat1',
                executable='NodeControl', # nom de l'executable
                name='nodeControl', # nom du node lors du lancement
                parameters=[config]
        )
        nodeCi = Node(
                package='td2', # nom du package
                namespace='bat1',
                executable='NodeCible', # nom de l'executable
                name='nodeCible', # nom du node lors du lancement
                parameters=[config]
        )
        return LaunchDescription([
                nodeS,
                nodeC,
                nodeCi
        ])
