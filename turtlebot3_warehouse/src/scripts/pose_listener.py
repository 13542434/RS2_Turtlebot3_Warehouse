#!/usr/bin/env python
import rospy
from geometry_msgs.msg import PoseWithCovarianceStamped

# Global variable to store the latest pose
current_pose = None

def pose_callback(msg):
    global current_pose
    # Extract the pose from the incoming message and store it in the global variable
    current_pose = msg.pose.pose
    rospy.loginfo("Updated current pose:\n%s", current_pose)

def pose_listener():
    rospy.init_node('amcl_pose_listener', anonymous=True)
    rospy.Subscriber("/tb3_0/amcl_pose", PoseWithCovarianceStamped, pose_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        pose_listener()
    except rospy.ROSInterruptException:
        pass

