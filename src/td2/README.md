# TP2 ROS : Les outils de développements de ROS 2

## 1 Design d’une architecture

### 1.1 Présentation du problème

#### Question 1.

```
arne@arne-G3-3500:~$ cd ~/workspaceTdRos/src
ros2 pkg create --build-type ament_cmake td2 --dependencies rclcpp example_interfaces tf2 geometry_msgs tf2_geometry_msgs

Aborted!
The directory already exists: ./td2
Either remove the directory or choose a different destination directory or package name
arne@arne-G3-3500:~/workspaceTdRos/src$ ros2 pkg create --build-type ament_cmake td2 --dependencies rclcpp example_interfaces tf2 geometry_msgs tf2_geometry_msgs
going to create a new package
package name: td2
destination directory: /home/arne/workspaceTdRos/src
package format: 3
version: 0.0.0
description: TODO: Package description
maintainer: ['arne <arne.jacobs@ensta-bretagne.com>']
licenses: ['TODO: License declaration']
build type: ament_cmake
dependencies: ['rclcpp', 'example_interfaces', 'tf2', 'geometry_msgs', 'tf2_geometry_msgs']
creating folder ./td2
creating ./td2/package.xml
creating source and include folder
creating folder ./td2/src
creating folder ./td2/include/td2
creating ./td2/CMakeLists.txt

[WARNING]: Unknown license 'TODO: License declaration'.  This has been set in the package.xml, but no LICENSE file has been created.
It is recommended to use one of the ament license identitifers:
Apache-2.0
BSL-1.0
BSD-2.0
BSD-2-Clause
BSD-3-Clause
GPL-3.0-only
LGPL-3.0-only
MIT
MIT-0
arne@arne-G3-3500:~/workspaceTdRos/src$ cd ..
arne@arne-G3-3500:~/workspaceTdRos$ colcon build --packages-select td2
Starting >>> td2     
Finished <<< td2 [2.24s]                  

Summary: 1 package finished [3.20s]
```

### 1.2 Rappels & Aide

## 2 Simulateur du bateau

### 2.1 Premiers pas

#### Question 2.

