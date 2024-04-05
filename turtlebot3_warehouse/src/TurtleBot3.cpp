#include "turtlebot3_warehouse/TurtleBot3.h"

TurtleBot3::TurtleBot3(ros::NodeHandle& nh) {
    pose_subs_[0] = nh.subscribe("/tb3_0/amcl_pose", 10, &TurtleBot3::poseCallback0, this);
    pose_subs_[1] = nh.subscribe("/tb3_1/amcl_pose", 10, &TurtleBot3::poseCallback1, this);
    pose_subs_[2] = nh.subscribe("/tb3_2/amcl_pose", 10, &TurtleBot3::poseCallback2, this);
}

void TurtleBot3::poseCallback0(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    current_poses_[0] = msg->pose.pose;
    pose_updated_[0] = true;
}

void TurtleBot3::poseCallback1(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    current_poses_[1] = msg->pose.pose;
    pose_updated_[1] = true;
}

void TurtleBot3::poseCallback2(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    current_poses_[2] = msg->pose.pose;
    pose_updated_[2] = true;
}

geometry_msgs::Pose TurtleBot3::getCurrentPose(int turtlebot_id) const {
    if(turtlebot_id >= 0 && turtlebot_id < current_poses_.size()) {
        return current_poses_[turtlebot_id];
    } else {
        ROS_WARN("Requested TurtleBot ID is out of range. Returning pose for TB3_0.");
        return current_poses_[0];
    }
}

bool TurtleBot3::hasPoseBeenUpdated(int turtlebot_id) const {
    if(turtlebot_id >= 0 && turtlebot_id < pose_updated_.size()) {
        return pose_updated_[turtlebot_id];
    } else {
        return false;
    }
}

void TurtleBot3::resetPoseUpdateFlag(int turtlebot_id) {
    if(turtlebot_id >= 0 && turtlebot_id < pose_updated_.size()) {
        pose_updated_[turtlebot_id] = false;
    }
}
