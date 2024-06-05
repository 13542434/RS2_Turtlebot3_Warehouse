#!/usr/bin/env python

import rospy
from std_msgs.msg import Bool
from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import PoseStamped


# Global variables to track subscription and publication status
global goal_request_publisher, goal_poses_subscriber


goals_received = None
goal_request_publisher = None
goal_poses_subscriber = None


def keyboard_input_callback(event):
    key = raw_input("Press 'a' to send goal request: ")
    if key == "a":
        rospy.loginfo("Sending goal request...")
        goal_request_publisher.publish(True)
        

def goal_pose_array_callback(data):

    global goals_received
    goals_received = PoseArray()
    goals_received = data

    #publish to /goal_requests  to reset the flag raised when requesting flag is TRUE
    goal_request_publisher.publish(False)
    rospy.loginfo("goal pose array received and request Flag is now False")
    goal_request_publisher.unregister()
    #goal_poses_subscriber.unregister()



def  publishPoseStampedToMoveBase(PoseData):
   
    # Create a new PoseStamped message
    data=PoseStamped()
    #rospy.init_node('PoseStamped_goal_publish_node',anonymous=False)
    publisher=rospy.Publisher('/move_base_simple/goal',PoseStamped,queue_size=10)

    rospy.sleep(1)
    data.header.seq = 0  
    data.header.stamp = rospy.Time.now()
    data.header.frame_id="map"
    data.pose.position=PoseData.position
    data.pose.orientation=PoseData.orientation

    #publish the pose Stamped
    publisher.publish(data)
def main():
    rospy.init_node('goals_pose_array_run_node')
    goal_request_publisher = rospy.Publisher('/goal_request', Bool, queue_size=10)
    goal_poses_subscriber = rospy.Subscriber('/goal_poses_array', PoseArray, goal_pose_array_callback)

    #Start requesting goal poses
    rospy.Timer(rospy.Duration(0.1), keyboard_input_callback)

    rate = rospy.Rate(10)  # 10 Hz

   

    # Spin to keep the node running
    rospy.spin()


    if __name__ == '__main__':
        main()