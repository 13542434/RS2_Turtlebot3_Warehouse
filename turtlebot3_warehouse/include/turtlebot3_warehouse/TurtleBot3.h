#ifndef TURTLEBOT3_H
#define TURTLEBOT3_H

#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <array>

class TurtleBot3 {
public:
    TurtleBot3(ros::NodeHandle& nh);
    geometry_msgs::Pose getCurrentPose(int turtlebot_id) const;
    bool hasPoseBeenUpdated(int turtlebot_id) const;
    void resetPoseUpdateFlag(int turtlebot_id);

private:
    void poseCallback0(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
    void poseCallback1(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
    void poseCallback2(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);

    std::array<geometry_msgs::Pose, 3> current_poses_;
    std::array<bool, 3> pose_updated_{false, false, false};
    std::array<ros::Subscriber, 3> pose_subs_;
};

#endif // TURTLEBOT3_H
