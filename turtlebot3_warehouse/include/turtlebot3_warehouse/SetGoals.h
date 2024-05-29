#ifndef SET_GOALS_H
#define SET_GOALS_H

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseArray.h"
#include "geometry_msgs/Pose.h"

class SetGoals {
public:
    SetGoals(ros::NodeHandle* nodehandle);
    void publishGoals();
    void publishGoalArray(geometry_msgs::PoseArray goalArray);

private:
    ros::NodeHandle nh;
    ros::Publisher goal_pub_tb3_0;
    ros::Publisher goal_pub_tb3_1;
    ros::Publisher goalArray_pub;

    void publishGoal(double x, double y, std::string frame_id, ros::Publisher& pub);
};

#endif
