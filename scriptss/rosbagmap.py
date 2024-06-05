#!/usr/bin/env python

import rosbag
import rospy

def remap_topic(topic):
    # Remove the '/robot3/' prefix from the topic name
    return topic.replace('/robot3/', '/')

def remap_bag(input_bag, output_bag):
    with rosbag.Bag(output_bag, 'w') as outbag:
        for topic, msg, t in rosbag.Bag(input_bag).read_messages():
            # Remap the topic name
            remapped_topic = remap_topic(topic)
            outbag.write(remapped_topic, msg, t)

if __name__ == '__main__':
    import argparse
    
    parser = argparse.ArgumentParser(description='Remap topics by removing "/robot3/" prefix from a ROS bag file.')
    parser.add_argument('input_bag', help='Input ROS bag file')
    parser.add_argument('output_bag', help='Output ROS bag file')

    args = parser.parse_args()

    try:
        remap_bag(args.input_bag, args.output_bag)
    except Exception as e:
        rospy.logerr('Error remapping bag: {}'.format(str(e)))
