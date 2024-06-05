#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
import time
        
def pub_cmd_vel_rotate_stop( x_linear,z_angular, time): # type: (float, float, int)-> None


    #Innit node cmd_vel_publisher with a unique ID
    rospy.init_node('cmd_vel_localisation_node',anonymous=True)
    print("Node cmd_vel_localisation_node init")

    #Create a publisher object publishes to topic cmd_vel, type Twist
    cmd_vel_pub= rospy.Publisher('/cmd_vel',Twist,queue_size=10)

    rospy.sleep(1)

    #Create object type Twist
    cmd_vel=Twist()
    cmd_vel.linear.x=x_linear
    cmd_vel.angular.z=z_angular

    #Publish the information using the publishing object
    cmd_vel_pub.publish(cmd_vel)

     # Sleep for the specified duration
    rospy.loginfo("Waiting for {} seconds...".format(time))
    rospy.sleep(time)

    # Stop the robot by publishing zero velocities
    rospy.loginfo("Stopping the robot")
    cmd_vel.linear.x = 0.0
    cmd_vel.angular.z = 0.0
    cmd_vel_pub.publish(cmd_vel)


if __name__ == "__main__":

    print("Node not init")
    linear_x= float(input("Input Linear Velocity from ~ +-0.26  " ))
    angular_z= float(input("Input Angular Velocity from ~ +-1.82  "))
    time= int(input("Input time for rotation from 5-30 "))

    pub_cmd_vel_rotate_stop(linear_x,angular_z,time)

































