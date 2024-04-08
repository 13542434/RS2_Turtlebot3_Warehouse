#include "turtlebot3_warehouse/MultiBot.h"
#include <cmath>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/GetPlan.h>
#include <fstream>

MultiBot::MultiBot(ros::NodeHandle* nh) : nh_(*nh), turtleBot3_(*nh) {
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

void MultiBot::calculateLivePlans() {
    //open the CSV file
    std::ofstream file("../plans.csv");

    //check if you cannot open it
    if (!file.is_open()) {
        ROS_ERROR("Failed to open file to write plans.");
        return;
    }
    //top row of the csv file for the columns
    file << "Start,End,Distance\n";

    for (int tb = 0; tb < 3; ++tb) { //loop through three turtlebots atm

        if (!turtleBot3_.hasPoseBeenUpdated(tb)) { //check that we have received AMCL_pose data (from the localisation)
            ROS_WARN("Pose for TurtleBot %d not updated yet. Waiting...", tb);
            while (!turtleBot3_.hasPoseBeenUpdated(tb)) {
                ros::spinOnce();
                ros::Duration(0.1).sleep();
            }
        }
        std::string service_name = "/tb3_" + std::to_string(tb) + "/move_base/make_plan"; 
        ros::ServiceClient client = nh_.serviceClient<nav_msgs::GetPlan>(service_name);
        geometry_msgs::Pose start_pose = turtleBot3_.getCurrentPose(tb); //get the current position of the turtlebot from amcl

        std::string startLocation = "Robot" + std::to_string(tb);
        ROS_INFO("[Robot %d] Generating plans. Start Pose: x=%.2f, y=%.2f, z=%.2f",
                 tb, start_pose.position.x, start_pose.position.y, start_pose.position.z);

        for (size_t i = 0; i < packageCoordinates.size(); ++i) { //loop through each package location
            const auto& coord = packageCoordinates[i];

            nav_msgs::GetPlan srv; //outline the goal position using data from packageCoordinates (from void loadPackages)
            srv.request.start.header.frame_id = "map";
            srv.request.start.pose = start_pose;
            srv.request.goal.header.frame_id = "map";
            srv.request.goal.pose.position.x = std::get<0>(coord);
            srv.request.goal.pose.position.y = std::get<1>(coord);
            srv.request.goal.pose.position.z = 0;
            srv.request.goal.pose.orientation.w = 1;

            if (client.call(srv)) {
                double distance = calculatePlanDistance(srv.response.plan); //get path distance
                std::string packageNumber = "Package" + std::to_string(i + 1);

                // ROS_INFO("[Robot %d] Plan to %s: Start (x=%.2f, y=%.2f) -> Goal (x=%.2f, y=%.2f) Distance: %.2f",
                //          tb, packageNumber.c_str(),
                //          start_pose.position.x, start_pose.position.y,
                //          std::get<0>(coord), std::get<1>(coord), distance);

                if (distance == 0.00) {
                    ROS_WARN("[Robot %d] Plan to %s may be off the map or unreachable.",
                             tb, packageNumber.c_str());
                } else {
                    //save the path length to the CSV file
                    ROS_INFO_STREAM(startLocation << " plan distance to " << packageNumber << ": " << distance);
                    file << startLocation << "," << packageNumber << "," << distance << "\n";
                }
            } else {
                ROS_ERROR("[Robot %d] Failed to call service %s", tb, service_name.c_str());
            }
            ros::Duration(0.1).sleep();
        }
    }

    file.close();
}


void MultiBot::calculateFuturePlans() {
    // Open the CSV file for writing future plan distances
    std::ofstream file("../plans.csv", std::ios::app);

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



void MultiBot::loadPackages(){

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    //here, take in a csv file that has x number of coordinates of packages on the map. 
    // Unforunately, i think you need to update this manually at this time, or write a prompt for console to enter the correct path.
    // Seems the GCC compiler this version uses doesn't support std::filesystem :(

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::ifstream file("../package_orders.csv");
    std::string line;
    
    //Check if file is open
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::istringstream sstream(line);
        std::string field;
        std::vector<double> coordinates;

        // Split line by comma and convert to double
        while (std::getline(sstream, field, ',')) {
            coordinates.push_back(std::stod(field));
        }

        // Assuming each line has exactly 3 coordinates (x, y, z)
        if (coordinates.size() == 3) {
            packageCoordinates.push_back(std::make_tuple(coordinates[0], coordinates[1], coordinates[2]));
        }
        
    }

    // After loading the coordinates and closing the file:
        std::cout << "Loaded package coordinates:" << std::endl;
        for (const auto& coord : packageCoordinates) {
            std::cout << "(" 
                    << std::get<0>(coord) << ", " 
                    << std::get<1>(coord) << ", " 
                    << std::get<2>(coord) << ")" 
                    << std::endl;
        }


    file.close();
}