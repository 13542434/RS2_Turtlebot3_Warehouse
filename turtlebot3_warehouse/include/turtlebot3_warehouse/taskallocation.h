#ifndef TASKALLOCATION_H
#define TASKALLOCATION_H

#include <vector>
#include "order.h"
#include "turtlebot3.h"
#include <string>
using namespace std;

// Include any other header files this class relies on

class TaskAllocation 
{
public:
    // Default Constructors
    TaskAllocation();

    /**
     * MultiRobot gets their goals from here [[TB1, startLoc, endLoc], [TB2, startLoc, endLoc]]
     *  
     */
    void assignedGoals(void);
    /**
     * Takes package orders from warehouse system (.csv) and converts them to vectors of Orders [order1, order2], where an order is [pkg#, pickUpLoc, dropOffLoc]
     * Runs once in constructor to set up
     * @return true if packages have all been read correctly
    */
    bool convertPackageOrders(void);
    /**
     * @return the orders converted from the csv file
    */
    std::vector<Order> getOrders(void);
    
protected:

private:
    // Functionality not used elsewhere goes here

    /**
     * Assigns package orders to currently available turtlebots via nearest neighbour greedy allocation
    */
    bool nearestNeighbour(void);

    std::vector<Order> orders_;

    std::vector<TurtleBot3> turtlebots_;

};

#endif // TASKALLOCATION_H