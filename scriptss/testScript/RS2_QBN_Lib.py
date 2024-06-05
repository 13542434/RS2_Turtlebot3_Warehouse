#!/usr/bin/env python
from geometry_msgs.msg import Quaternion
import tf

def get_yaw_from_orientation(orientation):
    #Orientation need to ba a data type where it has x,y,z,w component

    #Organise input data
    quaternion = [orientation.x, orientation.y, orientation.z, orientation.w]

    #Ultilise function eular_from_quaternion from tf.transformation
    euler = tf.transformations.euler_from_quaternion(quaternion)

    # Yaw is the third element in the Euler angles (in radians)(Roll,Pitch,Yaw)
    yaw = euler[2]

    return yaw

