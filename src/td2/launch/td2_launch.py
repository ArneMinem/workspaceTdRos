from launch import LaunchDescription
from launch_ros.actions import Node

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

# Fonction appelé par ros2 launch pour avoir la liste des nodes à lancer
def generate_launch_description():
        node1 = Node(
                package='td1', # nom du package
                namespace='',
                executable='nodeA', # nom de l'executable
                name='node_A' # nom du node lors du lancement
        )
        node2 = Node(
                package='td2',
                namespace='',
                executable='NodeSimu',
                name='nodeSimu'
        )
        # retour de la fonction avec la liste des nodes à lancer
        return LaunchDescription([
                node1,
                node2
        ])


def generate_launch_description():
        config = os.path.join(
                get_package_share_directory('td2'),
                'config', # repertoire
                'td2.yaml'
        )
        return LaunchDescription([
                Node(
                        package='td2',
                        executable='NodeSimu',
                        namespace='',
                        name='nodeSimu',
                        parameters=[config] # variable contenant les paramètres chargés précédemment
                )
        ])