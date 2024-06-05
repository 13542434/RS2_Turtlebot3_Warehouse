#!/usr/bin/env python
import rospy

from std_msgs.msg import Bool
from geometry_msgs.msg import Pose
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import PoseWithCovarianceStamped
#from comparePoseAmclGaz_localisation import amcl_pose_callback
#from comparePoseAmclGaz_localisation import check_poses

flagvel0=Bool()

def  publishPoseStampedToMoveBase(PoseData):
   
    # Create a new PoseStamped message
    data=PoseStamped()
    #rospy.init_node('PoseStamped_goal_publish_node',anonymous=False)
    publisher=rospy.Publisher('/move_base_simple/goal',PoseStamped,queue_size=10)

    rospy.sleep(1)
    # Set the header sequence number
    data.header.seq = 0  

    # Set the header timestamp to the current time
    data.header.stamp = rospy.Time.now()

    #Set map frame
    data.header.frame_id="map"

    data.pose.position=PoseData.position
    data.pose.orientation=PoseData.orientation


    publisher.publish(data)

def goal_pose_callback(data):
    transform_goal = Pose()

    transform_goal.position = data.position
    transform_goal.orientation = data.orientation

    return transform_goal

def cmd_vel_callback(data):
    
    if data==0:
        flagVel0=True
    else:
        flagVel0=False

    return flagVel0

def goal_pose_array_callback(data):
#def compare_amcl_goal():
   
def robot_run_init():
    rospy.init_node('robot_run_node',anonymous=False)

    goal_request_publisher = rospy.Publisher('/goal_request', Bool, queue_size=10)

    #Subcriber to see when 
    rospy.Subscriber('/move_base_simple/goal', PoseStamped, goal_pose_array_callback)

    # rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, amcl_pose_callback)
    # rospy.Subscriber('/move_base_simple/goal',PoseStamped,goal_pose_callback)
    # rospy.Subscriber('/cmd_vel',Twist,cmd_vel_callback)


def main():

    robot_run_init()
    

    #Request goal need to be done here



    publishSudoPoseStampedToMoveBase(pose_vector[0])


if __name__ == '__main__':
    main()