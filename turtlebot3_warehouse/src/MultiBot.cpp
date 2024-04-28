#include "turtlebot3_warehouse/MultiBot.h"
#include "turtlebot3_warehouse/TurtleBot3.h"
#include "turtlebot3_warehouse/taskallocation.h"
#include <cmath>
#include <vector>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/GetPlan.h>
#include <fstream>
#include "turtlebot3_warehouse/order.h"

MultiBot::MultiBot(ros::NodeHandle* nh, TurtleBot3Interface tb3Interface, TaskAllocation taskAllocation, std::string include_file_path) : 
    nh_(*nh), turtleBot3Interface_(tb3Interface), taskAllocation_(taskAllocation), include_file_path_(include_file_path) 
{
    ROS_INFO("MultiBot initialised with TurtleBot3");
}

double MultiBot::calculateDistance(const geometry_msgs::PoseStamped& pose1, const geometry_msgs::PoseStamped& pose2) {
    double dx = pose1.pose.position.x - pose2.pose.position.x;
    double dy = pose1.pose.position.y - pose2.pose.position.y;
    return std::sqrt(dx * dx + dy * dy);
}

double MultiBot::calculatePlanDistance(const nav_msgs::Path& path) {
    double total_distance = 0.0;
    if (path.poses.size() > 1) {
        for (size_t i = 0; i < path.poses.size() - 1; ++i) {
            total_distance += calculateDistance(path.poses[i], path.poses[i + 1]);
        }
    }
    return total_distance;
}

void MultiBot::calculateDepotPlans() {
    std::vector<TurtleBot3*> turtlebots = turtleBot3Interface_.getTurtleBotsList();
    int num_tb = turtleBot3Interface_.getNumTurtlebots();
<<<<<<< HEAD
    // Open the CSV file
=======
    //open the CSV file
>>>>>>> 061da4f35103c439a047580a95bfb6bb9530f363
    std::ofstream file(plans_file_path_);

    // Check if you cannot open it
    if (!file.is_open()) {
        ROS_ERROR("Failed to open file to write plans.");
        return;
    }
    // Top row of the CSV file for the columns
    file << "Start,End,Distance\n";

    // define the depot position
    geometry_msgs::PoseStamped depot_pose;
    depot_pose.pose.position.x = 0.0;
    depot_pose.pose.position.y = 0.0;
    depot_pose.pose.position.z = 0.0;
    depot_pose.pose.orientation.w = 1.0;

    for (int tb = 0; tb < num_tb; ++tb) {
        std::string service_name = "/tb3_" + std::to_string(tb) + "/move_base/make_plan"; 
        ros::ServiceClient client = nh_.serviceClient<nav_msgs::GetPlan>(service_name);

        std::string startLocation = "Depot";

        for (size_t i = 0; i < packageCoordinates.size(); ++i) { // Loop through each package location
            const auto& coord = packageCoordinates[i];

            nav_msgs::GetPlan srv; // Outline the goal position using data from packageCoordinates
            srv.request.start.header.frame_id = "map";
            srv.request.start.pose = depot_pose.pose;
            srv.request.goal.header.frame_id = "map";
            srv.request.goal.pose.position.x = std::get<0>(coord);
            srv.request.goal.pose.position.y = std::get<1>(coord);
            srv.request.goal.pose.position.z = 0;
            srv.request.goal.pose.orientation.w = 1;
            if (client.call(srv)) {
                double distance = calculatePlanDistance(srv.response.plan); // Get path distance
                std::string packageNumber = "Package" + std::to_string(i + 1);

                if (distance == 0.00) {
                    ROS_WARN("Depot Plan to %s may be off the map or unreachable.", packageNumber.c_str());
                } else {
                    // Save the path length to the CSV file
                    ROS_INFO_STREAM(startLocation << " plan distance to " << packageNumber << ": " << distance);
                    file << startLocation << "," << packageNumber << "," << distance << "\n";
                }
            } else {
                ROS_ERROR("Depot Failed to call service %s", service_name.c_str());
            }
            ros::Duration(0.1).sleep(); //delay service calls
        }
    }
    
    file.close(); //close the csv for later use after all saved

}


void MultiBot::calculateFuturePlans() {
    // Open the CSV file for writing future plan distances
    std::ofstream file(plans_file_path_, std::ios::app);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        ROS_ERROR("Failed to open file to write all future plans.");
        return;
    }

        ros::ServiceClient client = nh_.serviceClient<nav_msgs::GetPlan>("/tb3_0/move_base/make_plan");

    // Calculate distances between all possible pairs of goals
    for (size_t i = 0; i < packageCoordinates.size(); ++i) {
        for (size_t j = 0; j < packageCoordinates.size(); ++j) {
            if (i != j) {
                
                //loop through each package between each package
                //set the start and end point for the make_plan
                nav_msgs::GetPlan srv;
                srv.request.start.header.frame_id = "map";
                srv.request.start.pose.position.x = std::get<0>(packageCoordinates[i]);
                srv.request.start.pose.position.y = std::get<1>(packageCoordinates[i]);
                srv.request.start.pose.position.z = 0;
                srv.request.start.pose.orientation.w = 1;

                srv.request.goal.header.frame_id = "map";
                srv.request.goal.pose.position.x = std::get<0>(packageCoordinates[j]);
                srv.request.goal.pose.position.y = std::get<1>(packageCoordinates[j]);
                srv.request.goal.pose.position.z = 0;
                srv.request.goal.pose.orientation.w = 1;
                
                if (client.call(srv)) {
                    //calculate distance between start and end points using make_plan
                    double distance = calculatePlanDistance(srv.response.plan);
                    
                    if(distance == 0.00){
                        ROS_INFO("I think the plan is off the map");
                    }
                    else{
                        //save to CSV file
                        ROS_INFO("plan distance from package %zu to package %zu: %.2f meters", i + 1, j + 1, distance);
                        file << "Package" << i+1 << "," << "Package" << j+1 << "," << distance << std::endl;
                    }
                } else {
                    ROS_ERROR("Failed to call service make_plan for future plan calculation between package %zu and %zu", i + 1, j + 1);
                }
                ros::Duration(0.1).sleep();
            }
        }
    }

    file.close();
    ROS_INFO("future plan calculations completed and saved.");
}

<<<<<<< HEAD
void MultiBot::loadPackages() {
    // Retrieve the list of orders from taskAllocation
    std::vector<Order> orders = taskAllocation_.getOrders();

    // Assuming packageCoordinates is a vector of tuples (x, y, z)
    // Clear existing coordinates
    packageCoordinates.clear();

    // Process each order to extract package coordinates
    for (const Order& order : orders) {
      
        // Retrieve pick-up location coordinates
        unsigned int pickUpX = order.getPickUpLoc(); 
        unsigned int pickUpY = order.getPickUpLoc(); 
        unsigned int pickUpZ = 0; 

        // Retrieve drop-off location coordinates
        unsigned int dropOffX = order.getDropOffLoc(); 
        unsigned int dropOffY = order.getDropOffLoc(); 
        unsigned int dropOffZ = 0; 
        // Add to packageCoordinates
        packageCoordinates.emplace_back(std::make_tuple(pickUpX, pickUpY, pickUpZ));
        packageCoordinates.emplace_back(std::make_tuple(dropOffX, dropOffY, dropOffZ));
=======


void MultiBot::loadPackages(){

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    //here, take in a csv file that has x number of coordinates of packages on the map. 
    // Unforunately, i think you need to update this manually at this time, or write a prompt for console to enter the correct path.
    // Seems the GCC compiler this version uses doesn't support std::filesystem :(

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::vector<Order> orders = taskAllocation_.getOrders(); //use this vector to fill package coordinates information

    std::ifstream file(package_orders_file_path_);
    std::string line;
    
    //Check if file is open
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return;
>>>>>>> 061da4f35103c439a047580a95bfb6bb9530f363
    }
    ROS_INFO("loaded package coordinates in Multibot.cpp");
}

