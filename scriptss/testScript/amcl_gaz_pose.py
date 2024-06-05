#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Pose
from gazebo_msgs.msg import ModelStates 
from geometry_msgs.msg import Quaternion
import tf

flag= False


#Flags to prevent error when pose check with varariables created
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
       
        a=abs(get_yaw_from_orientation(pose1.orientation))-abs(get_yaw_from_orientation(pose2.orientation))
        print(a)
        flag = True
    else:
       flag = False
    return flag
       
def amcl_pose_callback(data):
    
    global amcl_dat, flag_amcl_pose
    amcl_dat= Pose()
    
   
    amcl_dat.position.x = data.pose.pose.position.x
    amcl_dat.position.y = data.pose.pose.position.y
    amcl_dat.position.z = data.pose.pose.position.z

   
    amcl_dat.orientation.x=data.pose.pose.orientation.x
    amcl_dat.orientation.y=data.pose.pose.orientation.y
    amcl_dat.orientation.z=data.pose.pose.orientation.z
    amcl_dat.orientation.w=data.pose.pose.orientation.w 

      

    flag_amcl_pose= True

    # eularangles=quaternion_to_euler(amcl_quaternion)
    # rospy.loginfo(eularangles.x)

    rospy.loginfo("Estimated AMCL pose [x:%s ] [y:%s][z:%s]",amcl_dat.position.x,amcl_dat.position.y,amcl_dat.position.z)
    rospy.loginfo("Estimated AMCL [yaw:%s ] ",get_yaw_from_orientation(amcl_dat.orientation))
    rospy.loginfo("----------------------------------")


def gazebo_bot_state_callback(data):
    global gazebo_bot_pose,flag_gazebo_pose
    gazebo_bot_pose=Pose()

    # print("Entering gazebo_bot_state_callback")

    gazebo_bot_pose.position=data.pose[2].position
    gazebo_bot_pose.orientation=data.pose[2].orientation

    flag_gazebo_pose=True
    # rospy.loginfo("Gazebo pose [x:%s ] [y:%s][z:%s]",gazebo_bot_pose.position.x, gazebo_bot_pose.position.y, gazebo_bot_pose.position.z)

    # rospy.loginfo("----------------------------------")
    # rospy.sleep(0.5)
 
    
    
def main():
    
    rospy.init_node('pose_Compare')

    rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, amcl_pose_callback)

    rospy.Subscriber('/gazebo/model_states', ModelStates, gazebo_bot_state_callback)


    rate = rospy.Rate(10)  # 10 Hz

    # Spin to prevent the script from exiting
    rospy.spin()


if __name__ == '__main__':
    main()
