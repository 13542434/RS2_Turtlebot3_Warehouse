#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "geometry_msgs/Pose.h"

// Include any other header files this class relies on

class Order
{
public:
    // Default Constructors
    Order(std::string include_file_path);
    Order(std::string include_file_path, unsigned int packageNo, unsigned int pickUpLoc, unsigned int dropOffLoc);

    void setPackageNo(unsigned int packageNo);
    void setPickUpLoc(unsigned int pickUpLoc);
    void setDropOffLoc(unsigned int dropOffLoc);    

    unsigned int getPackageNo(void) const;
    double getPickUpLoc(void) const;
    double getDropOffLoc(void) const;

    geometry_msgs::Pose getPickUpPose(void) const;
    geometry_msgs::Pose getDropOffPose(void) const;
    

private:
    // Functionality not used elsewhere goes here
    std::string include_file_path_;
    std::string addresses_file_path_ = include_file_path_ + "/turtlebot3_warehouse/addresses.csv";
    unsigned int packageNo_;
    unsigned int pickUpLoc_;
    unsigned int dropOffLoc_;
    geometry_msgs::Pose pickUpPose_;
    geometry_msgs::Pose dropOffPose_;
    geometry_msgs::Pose getPose(unsigned int location);

    geometry_msgs::Pose setPose(double x_coord, double y_coord, double z_coord, double roll, double pitch, double yaw);
    // std::vector<double> pickUpCoords_;
    // std::vector<double> dropOffCoords_;
    // std::vector<double> getCoordinates(unsigned int location);

};
#endif // ORDER_H