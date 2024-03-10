import sqlite3
from rosidl_runtime_py.utilities import get_message
from rclpy.serialization import deserialize_message
import rosbag2_py
import numpy as np
import datetime

import re
import matplotlib.pyplot as plt

bag_path='rosbag2_2024_02_16-14_17_44'
topic_name='/bat1/pos_bat' # several are allowed

serialization_format='cdr'
storage_options = rosbag2_py.StorageOptions(uri=bag_path, storage_id='sqlite3')
converter_options = rosbag2_py.ConverterOptions(
    input_serialization_format=serialization_format,
    output_serialization_format=serialization_format)


## Open the file
reader = rosbag2_py.SequentialReader()
reader.open(storage_options, converter_options)

## Get a map of all topics
topic_types = reader.get_all_topics_and_types()
type_map = {topic_types[i].name: topic_types[i].type for i in range(len(topic_types))}

## Filter to topic name
filter_topic = rosbag2_py.StorageFilter(topics=[topic_name])
reader.set_filter(filter_topic)

x_values = []
y_values = []

## Get the messages
while reader.has_next():
    try:
        (topic, data, t) = reader.read_next()

        try:
            msg_type = get_message(type_map[topic])
            msg = deserialize_message(data, msg_type)

            msg = str(msg)

            # Use regular expressions to extract the x, y, z coordinates
            positions = re.findall(r'Point\(x=(.*?), y=(.*?), z=(.*?)\)', msg)

            # Convert the extracted coordinates to a list of lists
            positions_array = np.array([[float(x), float(y), float(z)] for x, y, z in positions])
            positions_array = positions_array[0]

            x_values.append(positions_array[0])
            y_values.append(positions_array[1])

            print('x = ', positions_array[0], 'y = ', positions_array[1])

        except Exception as e:
            print("Oops!  deserialization error ", e)
            print(topic, data, t, msg_type)
            pass

    except Exception as e:
        print("Oops!  read_next error ", e)
        pass

plt.plot(x_values, y_values)
plt.show()