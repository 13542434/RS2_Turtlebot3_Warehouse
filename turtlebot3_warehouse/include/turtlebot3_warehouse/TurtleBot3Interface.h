#ifndef TURTLEBOT3INTERFACE_H
#define TURTLEBOT3INTERFACE_H

#include "ros/ros.h"
#include "turtlebot3_warehouse/TurtleBot3.h"
#include <array>
#include <vector>

class TurtleBot3Interface {
public:
    explicit TurtleBot3Interface(ros::NodeHandle* nh);
    std::vector<TurtleBot3*> getTurtleBotsList(void);
    int getNumTurtlebots(void);
private:
    ros::NodeHandle nh_;
    int num_turtlebots_;
    std::vector<TurtleBot3*> turtlebots_;
    int configSearch(std::string config_variable);
};

#endif // TURTLEBOT3INTERFACE_H
