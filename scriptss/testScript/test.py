#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Pose
from gazebo_msgs.msg import ModelState 



def gazebo_bot_state_callback(data):
    global gazebo_bot_pose
    gazebo_bot_pose=Pose()
    if len(data.pose) >= 3:
        
        gazebo_bot_pose.position=data.pose[2].position
        rospy.loginfo("Estimated pose [x:%s ] [y:%s][z:%s]",gazebo_bot_pose.position.x,gazebo_bot_pose.position.y,gazebo_bot_pose.position.z)

        rospy.loginfo("----------------------------------")
    else:
        rospy.logwarn("ModelState array does not contain enough elements")
    
def main():
 
    rospy.init_node('amcl_pose_subscriber')

    rospy.Subscriber('/gazebo/model_states', ModelState, gazebo_bot_state_callback)
    # Spin to prevent the script from exiting
    rospy.spin()

if __name__ == '__main__':
    main()
