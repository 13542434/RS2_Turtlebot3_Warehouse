#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Pose
from std_msgs.msg import Bool
from geometry_msgs.msg import PoseStamped

def goal_call_back(data):

    if data == True:
        sendData=PoseStamped()

        sendData.pose.position.x=0
        sendData.pose.position.y=0
        sendData.pose.position.z=0 
        
        sendData.pose.orientation.x=0
        sendData.pose.orientation.y=0
        sendData.pose.orientation.z=0
        sendData.pose.orientation.w=1

        goal_publisher.publish(sendData)

        goal_request_publisher.publish(False)


    else: 
        rospy.loginfo("Received goal request is False, no action needed.")



def main():
    
    rospy.init_node('goal_publish_node')
    
    rospy.Subscriber('/goal_request', Bool, goal_call_back)

    goal_request_publisher = rospy.Publisher('/goal_request', Bool, queue_size=10)
    goal_publisher = rospy.Publisher('/move_base_simple/goal',PoseStamped,queue_size=10)


#if /goal_request topic says True, send goal
    
    # Spin to prevent the script from exiting
    rospy.spin()


if __name__ == '__main__':
    main()
