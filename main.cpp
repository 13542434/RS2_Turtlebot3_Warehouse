#include "taskallocation.h"
#include <iostream>

int main(int argc, char *argv[]){
    TaskAllocation taskAllocation;
    taskAllocation.convertPackageOrders();
    std::cout << taskAllocation.myText_ << std::endl;
    // std::cout << "test" << std::endl;

    return 0;
}