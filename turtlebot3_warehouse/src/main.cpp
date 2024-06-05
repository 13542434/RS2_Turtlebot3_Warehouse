#include "ros/ros.h"
#include "turtlebot3_warehouse/SetGoals.h"
#include "turtlebot3_warehouse/MultiBot.h"
#include "turtlebot3_warehouse/TurtleBot3Interface.h"
#include "turtlebot3_warehouse/taskallocation.h"
#include "turtlebot3_warehouse/order.h"
#include <iostream>

int main(int argc, char** argv) {
    std::string include_file_path = "/home/qbn-ubun18/catkin_ws/turtlebot3_warehouse/include"; // Change this to your own directory path
    ros::init(argc, argv, "multi_bot");
    ros::NodeHandle nh;
    bool running = true;
    bool newGoalFlag;

    TurtleBot3Interface tb3Interface(&nh, include_file_path);

    TaskAllocation taskAllocation(tb3Interface, include_file_path);

    SetGoals setGoals(&nh);

    // Optional: wait a bit for subscribers to connect
    ros::Duration(1.0).sleep(); // Sleep for a second, adjust as needed

    // setGoals.publishGoals();

    // // Initialise MultiBot or any other components
    // MultiBot multiBot(&nh, tb3Interface, taskAllocation, include_file_path);
  
    // // ros::Duration(1.0).sleep();
    // multiBot.loadPackages();
    // // Testing the LKH solver currently don't use these plans as they are not generated correctly yet
    // // DO NOT USE // multiBot.calculateDepotPlans();
    // multiBot.calculateFuturePlans();

    // // Create TSP package allocations (occurs once for all packages before system runs)
    // taskAllocation.executeTSP();

    // controllerCallback --> bool for new goal
    Controller controller(&nh);
    pair<double, double> goal;
    while (running)
    {
        // for now this doesn't stop running
        newGoalFlag = controller.getNewGoalFlag();
        if (newGoalFlag) {
            goal = taskAllocation.controlGoalPasser();
            setGoals.publishGoals(goal.first, goal.second); //for now just publishing to tb3_0
        }
    }
    
    

    // Now enter the ROS event processing loop
    ros::spin();
    


    return 0;
}
