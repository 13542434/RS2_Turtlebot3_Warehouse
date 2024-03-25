#include "taskallocation.h"
using namespace std;
#include <iostream>
#include <fstream>

TaskAllocation::TaskAllocation() {
    bool converted = convertPackageOrders();
}

bool TaskAllocation::convertPackageOrders(void){
    bool converted = true;
    // read in .csv file

    ifstream package_orders_file("package_orders.csv");
    string myText;

    while (getline (package_orders_file, myText)) {
    // Output the text from the file
    std::cout << myText << std::endl;
    }

    return converted;
    
}

bool TaskAllocation::nearestNeighbour(void){
    bool executed = true;
    return executed;
}


