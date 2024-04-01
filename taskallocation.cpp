#include "taskallocation.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

TaskAllocation::TaskAllocation() {
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

bool TaskAllocation::nearestNeighbour(void){
    bool executed = true;
    return executed;
}


