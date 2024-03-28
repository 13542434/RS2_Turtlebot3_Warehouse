#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Pose


def amcl_pose_callback(data):

    #data is going to be under type PoseWithCovarianceStamped
    dat=Pose()
   
    dat.position. = data.pose.pose.position.x
    dat.y = data.pose.pose.position.y
    dat.z = data.pose.pose.position.z
    
    rospy.loginfo("Estimated pose [x:%s ] [y:%s][z:%s]",dat.x,dat.y,dat.z)
   # rospy.loginfo("Estimated pose y: %s",dat.y)
    #rospy.loginfo("Estimated pose z: %s",dat.z)
    rospy.loginfo("----------------------------------")

def main():
    rospy.init_node('amcl_pose_subscriber')
    # Subscribe to the /amcl_pose topic with the specified callback function
    rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, amcl_pose_callback)
    # Spin to prevent the script from exiting
    rospy.spin()

if __name__ == '__main__':
    main()