#!/usr/bin/env python
import rospy
from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose

def main():
    rospy.init_node('goal_pose_publish_array_node',anonymous=False)

    goal_request_publisher = rospy.Publisher('/goal_poses_array',PoseArray , queue_size=10)


    # Create an empty list to hold Pose messages
    pose_vector = []

    goal1=Pose()
    goal1.position.x = -5.95781230927
    goal1.position.y = 4.01864719391
    goal1.position.z = 0
    goal1.orientation.x =0
    goal1.orientation.y =0
    goal1.orientation.z =-0.00258446965429
    goal1.orientation.w =0.999996660253

    goal2=Pose()
    goal2.position.x = -6.51999902725
    goal2.position.y = -0.639999091625
    goal2.position.z = 0
    goal2.orientation.x =0
    goal2.orientation.y =0
    goal2.orientation.z =0.673563528904
    goal2.orientation.w =0.739129334102


    goal3=Pose()
    goal3.position.x = 1.05887103081
    goal3.position.y = 2.9848484993
    goal3.position.z = 0
    goal3.orientation.x =0
    goal3.orientation.y =0
    goal3.orientation.z =-0.707106838788
    goal3.orientation.w =0.707106723585
    
    goal4=Pose()
    goal4.position.x = 5.41717529297
    goal4.position.y = -2.46302080154
    goal4.position.z = 0
    goal4.orientation.x =0
    goal4.orientation.y =0
    goal4.orientation.z =-0.725451865473
    goal4.orientation.w =0.688272904364

   
    pose_vector.append(goal1)
    pose_vector.append(goal2)
    pose_vector.append(goal3)
    pose_vector.append(goal4)

   # Create PoseArray and populate it with poses
    pose_array = PoseArray()
    pose_array.poses = pose_vector
    
    #Sleep so Node has time to innit before publishing
    rospy.sleep(2)
    goal_request_publisher.publish(pose_array)

   

    # Give ROS some time to register the publisher
    rospy.spin()

 
if __name__ == '__main__':
    main()