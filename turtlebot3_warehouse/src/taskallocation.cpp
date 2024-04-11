#include "turtlebot3_warehouse/taskallocation.h"
#include "turtlebot3_warehouse/turtlebot3Interface.h"
#include "turtlebot3_warehouse/turtlebot3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

TaskAllocation::TaskAllocation(TurtleBot3Interface tb3Interface) :
    turtleBot3Interface_(tb3Interface)
{
    turtlebots_ = turtleBot3Interface_.getTurtleBotsList();
    convertPackageOrders();
}

bool TaskAllocation::convertPackageOrders(void){
    bool converted = true;
    vector<string> linesOfText;
    vector<Order> orders;

    ifstream package_orders_file("../package_orders.csv");
    string myText;
    char myChar;
    unsigned int orderState = 0;
    unsigned int packageNum = 0;
    unsigned int pickUpLoc = 0;
    unsigned int dropOffLoc = 0;

    if (package_orders_file.is_open())
    {
        while (package_orders_file)
        {
            myChar = package_orders_file.get();
            if (myChar != ' ' && myChar != ',' && myChar != ';' && myChar != '\n')
            {
                // cout<< myChar <<endl;
                // cout<< orderState <<endl;
                switch (orderState)
                {
                case 0:
                    packageNum = int(myChar) - 48;
                    // cout<< packageNum <<endl;                    
                    orderState++;
                    break;
                case 1:
                    pickUpLoc = int(myChar) - 48;
                    // cout<< pickUpLoc <<endl;  
                    orderState++;
                    break;
                case 2:
                    dropOffLoc = int(myChar) - 48;
                    // cout<< dropOffLoc <<endl;  
                    orderState = 0;
                    break;
                default:
                    orderState = 0;
                    break;
                }
            }

            if (packageNum!=0 && pickUpLoc!=0 && dropOffLoc!=0)
            {
                orders.push_back(Order(packageNum,pickUpLoc,dropOffLoc));
                packageNum = 0;
                pickUpLoc = 0;
                dropOffLoc = 0;
            }
            
            
        }
        
    }

    orders_ = orders;

    return converted;
    
}

std::vector<Order> TaskAllocation::getOrders(void){
    return orders_;
}

// make TSP graph <-- get the plans.csv and turn into a graph
// solve TSP using Vehicle Routing Problem (VRP)

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


