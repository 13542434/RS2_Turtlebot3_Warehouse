#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseArray     
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Quaternion
from gazebo_msgs.msg import ModelStates 
import tf
from RS2_QBN_Lib import get_yaw_from_orientation


class RS2_TurtleBot:
    #Class Innitialisation 
    def __init__(self):

        #Innitialise Ros node
        rospy.init_node("RS2_TurleBotMain",anonymous=False)
        rospy.Subscriber('/goal_poses_array',PoseArray,self.savePoseArray_)
        rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, self.amcl_pose_callback)
        # rospy.Subscriber('/gazebo/model_states', ModelStates, self.gazebo_bot_state_callback)
        # rospy.Subscriber('/gazebo/model_states', ModelStates, self.gazebo_bot_state_callback)
        rospy.Subscriber('/cmd_vel', Twist, self.cmdVel_callback)
        self.GoalPosePublisher=rospy.Publisher('/move_base_simple/goal',PoseStamped,queue_size=10)

        #Internal Variables
        self.amclPose_=    None
        self.amclIsReady_= False

        self.gazeboCurrentPose_=  None
        self.poseArray_ =   None
        self.posesNum = None
        self.poseArrayFlag_ = False
        self.currentGoalPose_= None

        self.goalPubSeq = 0
        self.currentGoalPoseIndex_ = 0  # Initialize the index to 0

        self.VelInfo_ = None
        self.velIsZero_=False
        self.cmdVelIsReady_ = False

        rospy.loginfo("Ready")
           

    def savePoseArray_(self, data):

        if isinstance(data, PoseArray):
            self.poseArray_ = data
            self.poseArrayFlag_=True # Flag indicating poses are now stored

            #Check Number of Poses
            self.posesNum = len(self.poseArray_.poses)
        
            rospy.loginfo("{} Goal Poses Received ".format(self.posesNum))
        else:
            rospy.logwarn("PoseArray Internal Variable Received an unknown message type")

    
    def  publishPoseStampedToMoveBase(self, PoseData):
   
        # Create a new PoseStamped message
        publisedPose = PoseStamped()
        #rospy.init_node('PoseStamped_goal_publish_node',anonymous=False)
        

        rospy.sleep(1)
        # Update sequence before assigning
        self.goalPubSeq += 1
         # Set the header sequence number
        publisedPose.header.seq = self.goalPubSeq  

        # Set the header timestamp to the current times
        publisedPose.header.stamp = rospy.Time.now()

        #Set map frame
        publisedPose.header.frame_id="map"

        publisedPose.pose.position=PoseData.position
        publisedPose.pose.orientation=PoseData.orientation


        self.GoalPosePublisher.publish(publisedPose)
    
    def printPose(self):
        if self.poseArrayFlag_ == True:
            print(self.poseArray_)

        else:               
            rospy.loginfo("No Pose Array Received")

    def amcl_pose_callback(self,data):
        if self.amclPose_ is None:
         self.amclPose_ = Pose()
        
    
      # Extract pose from PoseStamped message
        self.amclPose_.position = data.pose.pose.position
        self.amclPose_.orientation = data.pose.pose.orientation

        #Flag as part of a "TRUE AND" condition for comparison
        self.amclIsReady_= True

    def check_poses(self,pose1,pose2,positionTolerance,yawTolerance):
    

        if abs(pose1.position.x - pose2.position.x) < positionTolerance and \
        abs(pose1.position.y - pose2.position.y) < positionTolerance and \
        abs(pose1.position.z - pose2.position.z) < positionTolerance and \
        (abs(get_yaw_from_orientation(pose1.orientation))-abs(get_yaw_from_orientation(pose2.orientation)))<yawTolerance:
        
            flag = True
        else:
            flag = False   
        return flag

    def cmdVel_callback(self,data):
        self.cmdVelIsReady_ = True
        self.VelInfo_ = Twist()
        self.VelInfo_= data

        
        # Check if all components of linear and angular velocities are zero
        if data.linear.x == 0 and data.linear.y == 0 and data.linear.z == 0 and \
             data.angular.x == 0 and data.angular.y == 0 and data.angular.z == 0:
             self.velIsZero_ = True
        else:
            self.velIsZero_ = False
        
    def goal_achieved(self):
        if self.velIsZero_ and self.amclIsReady_ and self.currentGoalPose_:
            return self.check_poses(self.amclPose_, self.currentGoalPose_, 0.37, 0.2)
        return False



if __name__ == "__main__":

        ttb_1 = RS2_TurtleBot()


        rate = rospy.Rate(1.5)  # 1.5 Hz
        while not rospy.is_shutdown():
         if ttb_1.poseArrayFlag_:
            for idx in range(len(ttb_1.poseArray_.poses)):
                ttb_1.currentGoalPose_ = ttb_1.poseArray_.poses[idx]
                ttb_1.publishPoseStampedToMoveBase(ttb_1.currentGoalPose_)
                
                while not ttb_1.goal_achieved() and not rospy.is_shutdown():
                    rate.sleep()
                
                rospy.loginfo("Goal achieved, moving to next goal.")
                
                # Increment the current goal pose index
                ttb_1.currentGoalPoseIndex_ += 1
        rate.sleep()