#!/usr/bin/env python
import rospy
from geometry_msgs.msg import PoseStamped

def publish_goal():
    # Initialize the ROS Node
    rospy.init_node('publish_goal_node', anonymous=True)

    # Create a publisher object
    goal_publisher_tb3_0 = rospy.Publisher('/tb3_0/move_base_simple/goal', PoseStamped, queue_size=10)

    # Wait for the publisher to establish connection to subscribers
    rospy.sleep(1)

    # Create the goal message
    goal = PoseStamped()
    goal.header.seq = 0
    goal.header.stamp = rospy.Time.now()
    goal.header.frame_id = "map"
    goal.pose.position.x = 5.0
    goal.pose.position.y = 0.0
    goal.pose.position.z = 0.0
    goal.pose.orientation.x = 0.0
    goal.pose.orientation.y = 0.0
    goal.pose.orientation.z = 0.0
    goal.pose.orientation.w = 1.0

    # Log info
    rospy.loginfo("Publishing goal to /tb3_0/move_base_simple/goal")

    # Publish the message
    goal_publisher_tb3_0.publish(goal)
    
    # Create a publisher object
    goal_publisher_tb3_1 = rospy.Publisher('/tb3_1/move_base_simple/goal', PoseStamped, queue_size=10)

    # Wait for the publisher to establish connection to subscribers
    rospy.sleep(1)

    # Create the goal message
    goal = PoseStamped()
    goal.header.seq = 0
    goal.header.stamp = rospy.Time.now()
    goal.header.frame_id = "map"
    goal.pose.position.x = 3.0
    goal.pose.position.y = 0.0
    goal.pose.position.z = 0.0
    goal.pose.orientation.x = 0.0
    goal.pose.orientation.y = 0.0
    goal.pose.orientation.z = 0.0
    goal.pose.orientation.w = 1.0

    # Log info
    rospy.loginfo("Publishing goal to /tb3_1/move_base_simple/goal")

    # Publish the message
    goal_publisher_tb3_1.publish(goal)

    # Keep the script alive for a while
    rospy.sleep(3)

if __name__ == '__main__':
    try:
        publish_goal()
    except rospy.ROSInterruptException:
        pass

