#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Pose
from gazebo_msgs.msg import ModelStates 
from geometry_msgs.msg import Quaternion
import tf

flag= False

#Flags to prevent error when subcribers are set up, and main attempt to check for flags before run compare pose 
flag_gazebo_pose = False
flag_amcl_pose= False

def get_yaw_from_orientation(orientation):
    #Orientation need to ba a data type where it has x,y,z,w component

    #Organise input data
    quaternion = [orientation.x, orientation.y, orientation.z, orientation.w]

    #Ultilise function eular_from_quaternion from tf.transformation
    euler = tf.transformations.euler_from_quaternion(quaternion)

    # Yaw is the third element in the Euler angles (in radians)(Roll,Pitch,Yaw)
    yaw = euler[2]

    return yaw

def check_poses(pose1,pose2,positionTolerance,yawTolerance):
    global flag

    if abs(pose1.position.x - pose2.position.x) < positionTolerance and \
       abs(pose1.position.y - pose2.position.y) < positionTolerance and \
       abs(pose1.position.z - pose2.position.z) < positionTolerance and \
       (abs(get_yaw_from_orientation(pose1.orientation))-abs(get_yaw_from_orientation(pose2.orientation)))<yawTolerance:
       
       
        flag = True
    else:
       flag = False
       
    #    For debugging
    #    print("x diff=",abs(pose1.position.x - pose2.position.x))
    #    print("y diff=",abs(pose1.position.y - pose2.position.y))
    #    print("z diff=",abs(pose1.position.z - pose2.position.z))
    #    print("yaw diff=",(abs(get_yaw_from_orientation(pose1.orientation))-abs(get_yaw_from_orientation(pose2.orientation))))
    return flag
       
def amcl_pose_callback(data):
    
    global flag_amcl_pose,amcl_dat
    amcl_dat= Pose()
    #print("AMCL is working")
   #Assign function input data to global variable
    amcl_dat.position.x = data.pose.pose.position.x
    amcl_dat.position.y = data.pose.pose.position.y
    amcl_dat.position.z = data.pose.pose.position.z
    #(@_@)
    amcl_dat.orientation.x=data.pose.pose.orientation.x
    amcl_dat.orientation.y=data.pose.pose.orientation.y
    amcl_dat.orientation.z=data.pose.pose.orientation.z
    amcl_dat.orientation.w=data.pose.pose.orientation.w 

    #Flag as part of a "TRUE AND" condition for comparison
    flag_amcl_pose= True


def gazebo_bot_state_callback(data):
    global gazebo_bot_pose,flag_gazebo_pose
    gazebo_bot_pose=Pose()

    #print("gazebo is working")
    gazebo_bot_pose.position=data.pose[2].position
    gazebo_bot_pose.orientation=data.pose[2].orientation

    #Flag as part of a "TRUE AND" condition for comparison
    flag_gazebo_pose=True

    
def main():
    
    rospy.init_node('pose_Compare_node')
    
    rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, amcl_pose_callback)

    rospy.Subscriber('/gazebo/model_states', ModelStates, gazebo_bot_state_callback)


    rate = rospy.Rate(10)  # 10 Hz

    while not rospy.is_shutdown():
           
            
        if flag_amcl_pose and flag_gazebo_pose:

            #To set poses and tolerances 
            check_poses(amcl_dat, gazebo_bot_pose,0.37,0.2)

            if flag == True:
                 print("Poses are within telerance")
            else: 
                 print("Poses are NOT within telerance")
                 

        rate.sleep()

    # Spin to prevent the script from exiting
    rospy.spin()


if __name__ == '__main__':
    main()