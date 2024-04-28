#ifndef TURTLEBOT3INTERFACE_H
#define TURTLEBOT3INTERFACE_H

#include "ros/ros.h"
#include "turtlebot3_warehouse/TurtleBot3.h"
#include <array>
#include <vector>

class TurtleBot3Interface {
public:
    explicit TurtleBot3Interface(ros::NodeHandle* nh, std::string include_file_path);
    std::vector<TurtleBot3*> getTurtleBotsList(void);
    int getNumTurtlebots(void);
private:
    ros::NodeHandle nh_;
    int num_turtlebots_;
    std::vector<TurtleBot3*> turtlebots_;
    std::string include_file_path_;
    std::string config_file_path_ = include_file_path_ + "/turtlebot3_warehouse/config.txt";
<<<<<<< HEAD
    int configSearch(const std::string& config_variable);
=======
    int configSearch(std::string config_variable);
>>>>>>> 061da4f35103c439a047580a95bfb6bb9530f363
};

#endif // TURTLEBOT3INTERFACE_H
