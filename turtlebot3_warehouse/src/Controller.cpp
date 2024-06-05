#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Bool.h"

Controller::Controller(ros::NodeHandle* nh) :
nh_(nh*) {
    goal_request_sub_ = nh.subcribe<std_msgs::Bool>("goal_request_sender", 10, goalRequestCallback);
}

void Controller::goalRequestCallback(const std_msgs::Bool::ConstPtr& msg) {
    ROS_INFO("Received Bool: %s", msg->data.c_str());
    newGoalFlag_ = msg->data;
}

bool Controller::getNewGoalFlag(void) {
    goalRequestCallback(goal_request_sub_);
    return newGoalFlag_;
}