#include "turtlebot3_warehouse/taskallocation.h"
#include "turtlebot3_warehouse/order.h"
#include "turtlebot3_warehouse/TurtleBot3Interface.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

TaskAllocation::TaskAllocation(TurtleBot3Interface tb3Interface, std::string include_file_path) :
    turtleBot3Interface_(tb3Interface), include_file_path_(include_file_path)
{
    turtlebots_ = turtleBot3Interface_.getTurtleBotsList();
    convertPackageOrders();
}

bool TaskAllocation::convertPackageOrders(void){
    bool converted;
    std::vector<Order> orders;
    unsigned int orderState = 0;
    unsigned int packageNum = 0;
    std::string packageNum_str;
    unsigned int pickUpLoc = 0;
    std::string pickUpLoc_str;
    unsigned int dropOffLoc = 0;
    std::string dropOffLoc_str;
    std::ifstream package_orders_file(package_orders_file_path_);
    std::string myText;
    int counter = -1;

    if (package_orders_file.is_open())
    {
        std::cout << "package_orders.csv reads:" << std::endl;
        while (package_orders_file.good()) { 
            getline(package_orders_file, myText);
            std::cout << myText << std::endl;
            orderState = 0;
            
            if (counter >= 0) // skip first line (packageNo,pickUpLoc,dropOffLoc)
            {
                for (auto myChar:myText)
                {
                    switch (orderState)
                    {
                    case 0:
                        // all characters until next comma are the packageNum
                        if (myChar == ',')
                        {
                            packageNum = stoi(packageNum_str);
                            orderState++;
                            packageNum_str = "";
                        }
                        else
                        {
                            packageNum_str += myChar;
                        }                        
                        break;
                    case 1:
                        // all characters until next comma are the pickUpLoc
                        if (myChar == ',')
                        {
                            pickUpLoc = stoi(pickUpLoc_str);
                            orderState++;
                            pickUpLoc_str = "";
                        }
                        else
                        {
                            pickUpLoc_str += myChar;
                        }
                        break;
                    case 2:
                        // all characters until next comma are the dropOffLoc
                        if (myChar == ',')
                        {
                            dropOffLoc = stoi(dropOffLoc_str);
                            orderState = 0;
                            dropOffLoc_str = "";
                        }
                        else
                        {
                            dropOffLoc_str += myChar;
                        }
                        break;
                    default:
                        break;                        
                    }

                }            

                orders.push_back(Order(packageNum, pickUpLoc, dropOffLoc));
                packageNum = 0;
                pickUpLoc = 0;
                dropOffLoc = 0;
            }
            counter++;
            
        }        
    }
    else
    {
        std::cout << "package_orders.csv could not be read" <<std::endl;
        return converted = false;
    }

    std::cout << "Orders are:" << std::endl;
    for (auto order:orders)
    {
        std::cout << "packageNo: " << order.getPackageNo() << ", pickUpLoc: " << order.getPickUpLoc() << ", dropOffLoc: " << order.getDropOffLoc() << std::endl;
    }

    orders_ = orders;

    return converted = true;
    
}

std::vector<Order> TaskAllocation::getOrders(void){
    return orders_;
}

// make TSP graph <-- get the plans.csv and turn into a graph

// solve TSP using Vehicle Routing Problem (VRP)
//LKH-3 CVRP (Capacitated Vehicle Routing Problem)
// Get number of packages at each node from orders_ and transfer in csv
// execute the task_allocation.py (the paths in there need to change to work in git)

/*
bool TaskAllocation::nearestNeighbour(void){
    bool executed = true;
    vector<unsigned int> turtlebotNeighbourhood;
    vector<unsigned int> neighbouringPackages;
    unsigned int packageNo;
    double distance;
    vector<double> distances;
    double closestDistance;
    MultiRobot multiRobot; //MultiRobot Path Planning class


    // find available turtlebots
    for (auto turtlebot : turtlebots_)
    {
        if (!turtlebot.getHasPackage())
        {
            // find packages within vicinity of turtlebot's neighbourhood
            turtlebotNeighbourhood = turtlebot.getNeighbourhood();
            turtlebotNeighbourhood.push_back(9999);//for find algorithm to work
            for (auto order : orders_)
            {
                packageNo = order.getPackageNo();

                auto it = std::find(turtlebotNeighbourhood.begin(), turtlebotNeighbourhood.end(), packageNo);

                if (it != turtlebotNeighbourhood.end()) 
                {
                    //packages to assign to turtlebot
                    neighbouringPackages.push_back(packageNo);
                }
            }
            //find the closest neighbouringPackages to turtlebot
            
            for (auto assignedPackage : neighbouringPackages)
            {
                distance = multiRobot.getDistanceToPackage(turtlebot, assignedPackage);
                distances.push_back(distance);
            }
            distances.push_back(99999);//for find algorithm to work

            for (int i = 0; i < distances.size()-1; i++)
            {
                if(distances.at(i+1)<distances.at(i)){
                    closestDistance = distances.at(i+1);
                }
            }

            //get the index of closestDistance and assign correlated package number to turtlebot
            auto itDistance = std::find(distances.begin(), distances.end(), closestDistance);
            if (itDistance != distances.end()) 
            {
                //closest assignable package
                int index = itDistance - distances.end();
                assignPackageToTurtlebot(neighbouringPackages.at(index));
            }      
            
            
        }
        
    }
    
    
    // assign the packages to the turtlebot that are in the neighbourhood AND nearest to turtlebot
    return executed;
}
*/


// packagePoseAssociation??? (not sure depends on how MultiRobot works)


