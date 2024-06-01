#include "ros/ros.h"
#include "turtlebot3_warehouse/SetGoals.h"
#include "turtlebot3_warehouse/MultiBot.h"
#include "turtlebot3_warehouse/TurtleBot3Interface.h"
#include "turtlebot3_warehouse/taskallocation.h"
#include "turtlebot3_warehouse/order.h"
#include <iostream>

void goalPasserCallback(const ros::TimerEvent&, TaskAllocation& taskAllocation) {
    taskAllocation.goalPasser();
}

int main(int argc, char** argv) {
    std::string include_file_path = "/home/nk/catkin_ws/src/turtlebot3_warehouse/include"; // Change this to your own directory path
    ros::init(argc, argv, "multi_bot");
    ros::NodeHandle nh;

    TurtleBot3Interface tb3Interface(&nh, include_file_path);

    TaskAllocation taskAllocation(tb3Interface, include_file_path);

    SetGoals setGoals(&nh);

    // Optional: wait a bit for subscribers to connect
    ros::Duration(1.0).sleep(); // Sleep for a second, adjust as needed

    // setGoals.publishGoals();

    // Initialise MultiBot or any other components
    MultiBot multiBot(&nh, tb3Interface, taskAllocation, include_file_path);
  
    // ros::Duration(1.0).sleep();
    multiBot.loadPackages();
    // DO NOT USE, no longer need calculateDepotPlans // multiBot.calculateDepotPlans();
    multiBot.calculateFuturePlans();

    // Create TSP package allocations (occurs once for all packages before system runs)
    taskAllocation.executeTSP();
    std::cout<<"TESTING"<<std::endl;
    // geometry_msgs::PoseArray goalArray = taskAllocation.controlGoalArray();
    // setGoals.publishGoalArray(goalArray);

    // ros::Timer timer = nh.createTimer(ros::Duration(1.0), boost::bind(goalPasserCallback, _1, boost::ref(taskAllocation)));
    ros::Rate rate(1); // Adjust the rate as needed
    while (ros::ok()) {
        taskAllocation.goalPasser();
        ros::spinOnce(); 
        rate.sleep();
    }
    // Now enter the ROS event processing loop
    // ros::spin();

    return 0;
}
