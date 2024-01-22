# TP2 ROS

## 3 Découverte des topics et services

### 3.1 Les interfaces (topics et services)

#### Question 1.

Terminal 1 :
```
arne@arne-G3-3500:~$ cd workspacetdros/
arne@arne-G3-3500:~/workspacetdros$ ros2 topic pub -r 1 /boat_name std_msgs/String "data: hello"
publisher: beginning loop
publishing #1: std_msgs.msg.String(data='hello')

publishing #2: std_msgs.msg.String(data='hello')

publishing #3: std_msgs.msg.String(data='hello')

publishing #4: std_msgs.msg.String(data='hello')

publishing #5: std_msgs.msg.String(data='hello')

publishing #6: std_msgs.msg.String(data='hello')

publishing #7: std_msgs.msg.String(data='hello')

publishing #8: std_msgs.msg.String(data='hello')

publishing #9: std_msgs.msg.String(data='hello')
```
Terminal 2 :
```
arne@arne-G3-3500:~$ cd workspacetdros/
arne@arne-G3-3500:~/workspacetdros$ ros2 topic echo /boat_name
data: hello
---
data: hello
---
data: hello
---
data: hello
---
data: hello
---
```

Pour changer le nom du topic, sa fréquence et son message on fait :
```ros2 topic pub -r 2 /new_topic_name std_msgs/String "data: new_message_text"```
- 2 pour 2Hz
- /new_topic_name pour le nom du topic
- std_msgs/String est le message_type
- "data: new_message_text" est le message envoyé

#### Question 2.
```
arne@arne-G3-3500:~/workspacetdrosros2 interface show std_msgs/msg/Stringng
# This was originally provided as an example message.
# It is deprecated as of Foxy
# It is recommended to create your own semantically meaningful message.
# However if you would like to continue using this please use the equivalent in example_msgs.

string data
arne@arne-G3-3500:~/workspacetdros$ ros2 interface show std_msgs/msg/Float64
# This was originally provided as an example message.
# It is deprecated as of Foxy
# It is recommended to create your own semantically meaningful message.
# However if you would like to continue using this please use the equivalent in example_msgs.

float64 data
arne@arne-G3-3500:~/workspacetdros$ ros2 interface show sensor_msgs/msg/Imu
# This is a message to hold data from an IMU (Inertial Measurement Unit)
#
# Accelerations should be in m/s^2 (not in g's), and rotational velocity should be in rad/sec
#
# If the covariance of the measurement is known, it should be filled in (if all you know is the
# variance of each measurement, e.g. from the datasheet, just put those along the diagonal)
# A covariance matrix of all zeros will be interpreted as "covariance unknown", and to use the
# data a covariance will have to be assumed or gotten from some other source
#
# If you have no estimate for one of the data elements (e.g. your IMU doesn't produce an
# orientation estimate), please set element 0 of the associated covariance matrix to -1
# If you are interpreting this message, please check for a value of -1 in the first element of each
# covariance matrix, and disregard the associated estimate.

std_msgs/Header header
	builtin_interfaces/Time stamp
		int32 sec
		uint32 nanosec
	string frame_id

geometry_msgs/Quaternion orientation
	float64 x 0
	float64 y 0
	float64 z 0
	float64 w 1
float64[9] orientation_covariance # Row major about x, y, z axes

geometry_msgs/Vector3 angular_velocity
	float64 x
	float64 y
	float64 z
float64[9] angular_velocity_covariance # Row major about x, y, z axes

geometry_msgs/Vector3 linear_acceleration
	float64 x
	float64 y
	float64 z
float64[9] linear_acceleration_covariance # Row major x, y z
arne@arne-G3-3500:~/workspacetdros$ ros2 interface show  std_srvs/srv/Trigger
---
bool success   # indicate successful run of triggered service
string message # informational, e.g. for error messages
```
#### Question 3.

```
arne@arne-G3-3500:~/workspacetdros$ ros2 topic pub /cap std_msgs/msg/Float32 "data: 90.0"
publisher: beginning loop
publishing #1: std_msgs.msg.Float32(data=90.0)

publishing #2: std_msgs.msg.Float32(data=90.0)

publishing #3: std_msgs.msg.Float32(data=90.0)

publishing #4: std_msgs.msg.Float32(data=90.0)

publishing #5: std_msgs.msg.Float32(data=90.0)
```
#### Question 4.
```
arne@arne-G3-3500:~$ ros2 node list -a
/_ros2cli_10936
/_ros2cli_10958
/_ros2cli_daemon_0_7aed7b0ec37e4812b963993dd2d7a6d5
arne@arne-G3-3500:~$ ros2 node info /_ros2cli_10936 --include-hidden
/_ros2cli_10936
  Subscribers:

  Publishers:
    /cap: std_msgs/msg/Float32
    /parameter_events: rcl_interfaces/msg/ParameterEvent
    /rosout: rcl_interfaces/msg/Log
  Service Servers:

  Service Clients:

  Action Servers:

  Action Clients:

arne@arne-G3-3500:~$ ros2 node info /_ros2cli_10958 --include-hidden
/_ros2cli_10958
  Subscribers:
    /cap: std_msgs/msg/Float32
  Publishers:
    /parameter_events: rcl_interfaces/msg/ParameterEvent
    /rosout: rcl_interfaces/msg/Log
  Service Servers:

  Service Clients:

  Action Servers:

  Action Clients:

```
#### Question 5.

Les noms des nodes :
Publisher :
```
/_ros2cli_10936
```
Suscriber :
```
/_ros2cli_10958
```

#### Question 6.
```
workspaceTdRos/
    ├── build
    │   └── COLCON_IGNORE
    ├── install
    │   └── ...
    ├── log
    │   └── ...
```
#### Question 7.

```
arne@arne-G3-3500:~$ echo "source ~/workspaceTdRos/install/setup.bash" >> ~/.bashrc
arne@arne-G3-3500:~$ cat /home/arne/.bashrc
# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

...

source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
source ~/workspaceTdRos/install/setup.bash
```

#### Question 8.
```
workspaceTdRos/src/td1
    ├── CMakeLists.txt
    ├── include
    │   └── td1
    │       └── ...
    ├── package.xml
    ├── src
    │   └── ...
```
Il manque donc les fichiers msg et srv.

#### Question 9.

Terminal 1 :
```
arne@arne-G3-3500:~$ ros2 topic list
/parameter_events
/rosout
arne@arne-G3-3500:~$ ros2 topic list
/parameter_events
/rosout
/topic
arne@arne-G3-3500:~$ ros2 topic echo /topic
data: Hello, world! 48
---
data: Hello, world! 49
---
data: Hello, world! 50
---
data: Hello, world! 51
---
data: Hello, world! 52
---
data: Hello, world! 53
```

Terminal 2 :
```
arne@arne-G3-3500:~/workspaceTdRos$ ros2 run td1 nodeA
[INFO] [1705514248.261591230] [nodeA]: Publishing: 'Hello, world! 0'
[INFO] [1705514248.761679253] [nodeA]: Publishing: 'Hello, world! 1'
[INFO] [1705514249.261602256] [nodeA]: Publishing: 'Hello, world! 2'
[INFO] [1705514249.761627401] [nodeA]: Publishing: 'Hello, world! 3'
[INFO] [1705514250.261648498] [nodeA]: Publishing: 'Hello, world! 4'
[INFO] [1705514250.761634979] [nodeA]: Publishing: 'Hello, world! 5'
```

#### Question 10.

```
arne@arne-G3-3500:~/workspaceTdRos$ ros2 run td1 nodeA
[INFO] [1705662962.244105909] [nodeA]: Publishing: 'Sinusoid value: -0.929548'
[INFO] [1705662962.744038158] [nodeA]: Publishing: 'Sinusoid value: -0.992521'
[INFO] [1705662963.244044183] [nodeA]: Publishing: 'Sinusoid value: -0.812490'
[INFO] [1705662963.744040563] [nodeA]: Publishing: 'Sinusoid value: -0.433538'
[INFO] [1705662964.244035813] [nodeA]: Publishing: 'Sinusoid value: 0.051558'
[INFO] [1705662964.744040213] [nodeA]: Publishing: 'Sinusoid value: 0.524038'
[INFO] [1705662965.244042971] [nodeA]: Publishing: 'Sinusoid value: 0.868212'
[INFO] [1705662965.744038109] [nodeA]: Publishing: 'Sinusoid value: 0.999815'
[INFO] [1705662966.244037512] [nodeA]: Publishing: 'Sinusoid value: 0.886632'
[INFO] [1705662966.744041307] [nodeA]: Publishing: 'Sinusoid value: 0.556366'
[INFO] [1705662967.244048516] [nodeA]: Publishing: 'Sinusoid value: 0.089878'
[INFO] [1705662967.744041487] [nodeA]: Publishing: 'Sinusoid value: -0.398603'
[INFO] [1705662968.243986856] [nodeA]: Publishing: 'Sinusoid value: -0.789467'
[INFO] [1705662968.744042332] [nodeA]: Publishing: 'Sinusoid value: -0.987099'
[INFO] [1705662969.243961153] [nodeA]: Publishing: 'Sinusoid value: -0.943049'
[INFO] [1705662969.744038237] [nodeA]: Publishing: 'Sinusoid value: -0.668063'
[INFO] [1705662970.244040975] [nodeA]: Publishing: 'Sinusoid value: -0.229534'
^C[INFO] [1705662970.416065145] [rclcpp]: signal_handler(signum=2)
```
#### Question 11.

Terminal 1 :

```
arne@arne-G3-3500:~/workspaceTdRos$ ros2 topic pub /cap std_msgs/msg/Float32 "data: 90.0"
publisher: beginning loop
publishing #1: std_msgs.msg.Float32(data=90.0)

publishing #2: std_msgs.msg.Float32(data=90.0)

publishing #3: std_msgs.msg.Float32(data=90.0)

publishing #4: std_msgs.msg.Float32(data=90.0)

publishing #5: std_msgs.msg.Float32(data=90.0)

publishing #6: std_msgs.msg.Float32(data=90.0)

publishing #7: std_msgs.msg.Float32(data=90.0)

publishing #8: std_msgs.msg.Float32(data=90.0)

publishing #9: std_msgs.msg.Float32(data=90.0)
```

Terminal 2 :
```
arne@arne-G3-3500:~/workspaceTdRos$ ros2 run td1 nodeB
[INFO] [1705665711.360855280] [minimal_subscriber]: Received boat heading: '90.000000'
[INFO] [1705665712.360903022] [minimal_subscriber]: Received boat heading: '90.000000'
[INFO] [1705665713.360851706] [minimal_subscriber]: Received boat heading: '90.000000'
[INFO] [1705665714.360806769] [minimal_subscriber]: Received boat heading: '90.000000'
[INFO] [1705665715.360891126] [minimal_subscriber]: Received boat heading: '90.000000'
[INFO] [1705665716.360900701] [minimal_subscriber]: Received boat heading: '90.000000'
[INFO] [1705665717.360867246] [minimal_subscriber]: Received boat heading: '90.000000'
^C[INFO] [1705665717.883035506] [rclcpp]: signal_handler(signum=2)
```

#### Questions 12.

Voir code main_nodeA.cpp

#### Question 13.

Terminal 1 :
```
arne@arne-G3-3500:~/workspaceTdRos$ ros2 run td1 nodeA
[INFO] [1705748065.970632998] [nodeA]: Publishing: 'Sinusoid value: 0.734735'
[INFO] [1705748066.470650623] [nodeA]: Publishing: 'Sinusoid value: 0.319496'
[INFO] [1705748066.970613228] [nodeA]: Publishing: 'Sinusoid value: -0.173890'
[INFO] [1705748074.944724543] [nodeA]: État du moteur : On
[INFO] [1705748083.470612232] [nodeA]: Publishing: 'Sinusoid value: 0.823073'
[INFO] [1705748083.970531903] [nodeA]: Publishing: 'Sinusoid value: 0.994590'
[INFO] [1705748084.282870458] [nodeA]: État du moteur : On
[INFO] [1705748084.470569118] [nodeA]: Publishing: 'Sinusoid value: 0.922624'
[INFO] [1705748084.970592276] [nodeA]: Publishing: 'Sinusoid value: 0.624751'
[INFO] [1705748085.470651160] [nodeA]: Publishing: 'Sinusoid value: 0.173866'
[INFO] [1705748085.970611123] [nodeA]: Publishing: 'Sinusoid value: -0.319504'
[INFO] [1705748086.470501458] [nodeA]: Publishing: 'Sinusoid value: -0.734622'
[INFO] [1705748086.561074401] [nodeA]: État du moteur : On
[INFO] [1705748086.970636719] [nodeA]: Publishing: 'Sinusoid value: -0.970001'
[INFO] [1705748087.470645758] [nodeA]: Publishing: 'Sinusoid value: -0.967803'
^C[INFO] [1705748093.702579267] [rclcpp]: signal_handler(signum=2)
```

Terminal 2 :
```
ros2 service call /status_boat std_srvs/srv/Trigger "{}"
requester: making request: std_srvs.srv.Trigger_Request()

response:
std_srvs.srv.Trigger_Response(success=True, message='Nom du Bateau : Titanic, État du Moteur : On')

arne@arne-G3-3500:~/workspaceTdRos$ ros2 service call /status_boat std_srvs/srv/Trigger "{}"
requester: making request: std_srvs.srv.Trigger_Request()

response:
std_srvs.srv.Trigger_Response(success=True, message='Nom du Bateau : Titanic, État du Moteur : On')

arne@arne-G3-3500:~/workspaceTdRos$ ros2 service call /status_boat std_srvs/srv/Trigger "{}"
requester: making request: std_srvs.srv.Trigger_Request()

response:
std_srvs.srv.Trigger_Response(success=True, message='Nom du Bateau : Titanic, État du Moteur : On')
```