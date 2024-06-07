#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Pose
from gazebo_msgs.msg import ModelStates 
from geometry_msgs.msg import Quaternion
from geometry_msgs.msg import PoseStamped
import tf
from comparePoseAmclGaz_localisation import amcl_pose_callback
from comparePoseAmclGaz_localisation import get_yaw_from_orientation
from comparePoseAmclGaz_localisation import check_poses

def goal_call_back(data):
    transform_goal = Pose()

    transform_goal.position = data.position
    transform_goal.orientation = data.orientation
    


def main():
    
    rospy.init_node('pose_Compare_node')
    
    rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, amcl_pose_callback)

    rospy.Subscriber('/move_base_simple/goal', PoseStamped, goal_call_back)


    rate = rospy.Rate(10)  # 10 Hz

    while not rospy.is_shutdown():

        if flag_amcl_pose and flag_gazebo_pose:

            check_poses(amcl_dat, gazebo_bot_pose,0.35,0.2)

            if flag == True:
                 print("Poses are within telerance")
            else: 
                 print("Poses are NOT within telerance")

        rate.sleep()

    # Spin to prevent the script from exiting
    rospy.spin()


if __name__ == '__main__':
    main()