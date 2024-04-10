#include "turtlebot3_warehouse/TurtleBot3.h"

TurtleBot3::TurtleBot3(ros::NodeHandle* nh, std::string topic_string_) :
    nh_(*nh)
{
    pose_sub_ = nh_.subscribe(topic_string_, 10, &TurtleBot3::poseCallback, this);
}

void TurtleBot3::poseCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    current_pose_ = msg->pose.pose;
    pose_updated_ = true;
}

geometry_msgs::Pose TurtleBot3::getCurrentPose(void) const {
    return current_pose_;
}

bool TurtleBot3::hasPoseBeenUpdated(void) const {
    return pose_updated_;
}

void TurtleBot3::resetPoseUpdateFlag(void) {
    pose_updated_ = false;
}
