#ifndef TURTLEBOT3_H
#define TURTLEBOT3_H

#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <array>

class TurtleBot3 {
public:
    explicit TurtleBot3(ros::NodeHandle* nh, std::string topic_string_);
    geometry_msgs::Pose getCurrentPose(void) const;
    bool hasPoseBeenUpdated(void) const;
    void resetPoseUpdateFlag(void);

private:
    ros::NodeHandle nh_;
    void poseCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);

    geometry_msgs::Pose current_pose_;
    bool pose_updated_ = false;
    ros::Subscriber pose_sub_;
};

#endif // TURTLEBOT3_H
