#include "taskallocation.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

TaskAllocation::TaskAllocation() {
}

bool TaskAllocation::convertPackageOrders(void){
    bool converted = true;
    // read in .csv file
    // std::cout << "myText" << std::endl;

    ifstream package_orders_file("package_orders.txt");
    string myText;

    getline (package_orders_file, myText);
    // Output the text from the file    

    myText_ = myText;

    // Close the file
    package_orders_file.close(); 

    return converted;
    
}

bool TaskAllocation::nearestNeighbour(void){
    bool executed = true;
    return executed;
}


