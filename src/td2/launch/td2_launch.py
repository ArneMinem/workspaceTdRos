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
        nodeS1 = Node(
                package='td2', # nom du package
                namespace='bat1',
                executable='NodeSimu', # nom de l'executable
                name='nodeSimu', # nom du node lors du lancement
                parameters=[config]
        )
        nodeC1 = Node(
                package='td2', # nom du package
                namespace='bat1',
                executable='NodeControl', # nom de l'executable
                name='nodeControl', # nom du node lors du lancement
                parameters=[config]
        )
        nodeCi1 = Node(
                package='td2', # nom du package
                namespace='bat1',
                executable='NodeCible', # nom de l'executable
                name='nodeCible', # nom du node lors du lancement
                parameters=[config]
        )

        nodeS2 = Node(
                package='td2', # nom du package
                namespace='bat2',
                executable='NodeSimu', # nom de l'executable
                name='nodeSimu', # nom du node lors du lancement
                parameters=[config]
        )
        nodeC2 = Node(
                package='td2', # nom du package
                namespace='bat2',
                executable='NodeControl', # nom de l'executable
                name='nodeControl', # nom du node lors du lancement
                parameters=[config]
        )
        nodeCi2 = Node(
                package='td2', # nom du package
                namespace='bat2',
                executable='NodeCible', # nom de l'executable
                name='nodeCible', # nom du node lors du lancement
                parameters=[config]
        )

        nodeS3 = Node(
                package='td2', # nom du package
                namespace='bat3',
                executable='NodeSimu', # nom de l'executable
                name='nodeSimu', # nom du node lors du lancement
                parameters=[config]
        )
        nodeC3 = Node(
                package='td2', # nom du package
                namespace='bat3',
                executable='NodeControl', # nom de l'executable
                name='nodeControl', # nom du node lors du lancement
                parameters=[config]
        )
        nodeCi3 = Node(
                package='td2', # nom du package
                namespace='bat3',
                executable='NodeCible', # nom de l'executable
                name='nodeCible', # nom du node lors du lancement
                parameters=[config]
        )

        return LaunchDescription([
                nodeS1,
                nodeC1,
                nodeCi1,
                
                nodeS2,
                nodeC2,
                nodeCi2,

                nodeS3,
                nodeC3,
                nodeCi3
        ])
