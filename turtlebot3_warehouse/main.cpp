#include "taskallocation.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    TaskAllocation taskAllocation;
    for (auto order:taskAllocation.getOrders())
    {
        std::cout << order.getPackageNo() << ", " << order.getPickUpLoc() << ", " << order.getDropOffLoc() << std::endl;
    }   
    

    return 0;
}