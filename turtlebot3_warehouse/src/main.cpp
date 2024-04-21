#include "ros/ros.h"
#include "turtlebot3_warehouse/SetGoals.h"
#include "turtlebot3_warehouse/MultiBot.h"
#include "turtlebot3_warehouse/TurtleBot3Interface.h"
#include "turtlebot3_warehouse/taskallocation.h"
#include "turtlebot3_warehouse/order.h"
#include <iostream>

int main(int argc, char** argv) {
    ros::init(argc, argv, "multi_bot");
    ros::NodeHandle nh;

    TurtleBot3Interface tb3Interface(&nh);

    TaskAllocation taskAllocation(tb3Interface);

    SetGoals setGoals(&nh);

    // Optional: wait a bit for subscribers to connect
    ros::Duration(1.0).sleep(); // Sleep for a second, adjust as needed

    setGoals.publishGoals();

    // Initialise MultiBot or any other components
    MultiBot multiBot(&nh, tb3Interface);
  
    // ros::Duration(1.0).sleep();
    multiBot.loadPackages();
    multiBot.calculateLivePlans();
    multiBot.calculateFuturePlans();

    // Now enter the ROS event processing loop
    ros::spin();

    return 0;
}
