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
    ros::Publisher goal_pub_tb3_0;
    ros::Publisher goal_pub_tb3_1;
    ros::Publisher goal_pub_tb3_2;
    ros::Publisher goalArray_pub;

    void publishGoal(geometry_msgs::Pose pose, std::string frame_id, ros::Publisher& pub); 
private:

    ros::NodeHandle nh;
    
};

#endif
