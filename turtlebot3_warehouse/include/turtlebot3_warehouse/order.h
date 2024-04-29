#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

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

    unsigned int getPackageNo(void);
    unsigned int getPickUpLoc(void);
    unsigned int getDropOffLoc(void);
    
protected:

private:
    // Functionality not used elsewhere goes here
    std::string include_file_path_;
    std::string adresses_file_path_ = include_file_path_ + "/turtlebot3_warehouse/adresses.csv";
    unsigned int packageNo_;
    unsigned int pickUpLoc_;
    unsigned int dropOffLoc_;
    double x, y;
    std::vector<double> coords_;
    std::vector<double> getCoordinates(unsigned int location);

};
#endif // ORDER_H