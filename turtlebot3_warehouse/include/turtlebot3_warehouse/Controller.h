#include "ros/ros.h"
#include "turtlebot3_warehouse/SetGoals.h"
#include "turtlebot3_warehouse/MultiBot.h"
#include "turtlebot3_warehouse/TurtleBot3Interface.h"
#include "turtlebot3_warehouse/taskallocation.h"
#include "turtlebot3_warehouse/order.h"
#include <iostream>

class Controller
{
  public:
    Controller(ros::NodeHandle* nh);

    void goalRequestCallback(const std_msgs::Bool::ConstPtr& msg);

    bool getNewGoalFlag(void); 

  private:
  ros::NodeHandle* nh_;
  ros::Subscriber goal_request_sub_;
  bool newGoalFlag_ = false;
}