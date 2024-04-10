#ifndef MULTIBOT_H
#define MULTIBOT_H

#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"
#include "turtlebot3_warehouse/TurtleBot3Interface.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

class MultiBot {
public:
    explicit MultiBot(ros::NodeHandle* nh, TurtleBot3Interface tb3Interface);

    // void pathCallback(const nav_msgs::Path::ConstPtr& path_msg);
    double calculateDistance(const geometry_msgs::PoseStamped& pose1, const geometry_msgs::PoseStamped& pose2);
    void calculateLivePlans();
    void calculateFuturePlans();
    void loadPackages();  // Load packages from file
    double calculatePlanDistance(const nav_msgs::Path& path);

private:
    ros::NodeHandle nh_;
    TurtleBot3Interface turtleBot3Interface_;  // Instance of TurtleBot3Interface
    ros::Subscriber path_sub_;
    std::vector<std::tuple<double, double, double>> packageCoordinates;
    std::vector<double> planDistances_;  // Store distances of plans
};

#endif  // MULTIBOT_H
