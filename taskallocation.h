#ifndef TASKALLOCATION_H
#define TASKALLOCATION_H

#include <vector>
#include "order.h"

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
    
protected:

private:
    // Functionality not used elsewhere goes here
    /**
     * Takes package orders from warehouse system (.csv) and converts them to vectors [[pkg#, pickUpLoc, dropOffLoc], [pkg#, pickUpLoc, dropOffLoc]]
     * Runs once in constructor to set up
     * @return true if packages have all been read correctly
    */
    bool convertPackageOrders(void);

    /**
     * Assigns package orders to currently available turtlebots via nearest neighbour greedy allocation
    */
    bool nearestNeighbour(void);

    std::vector<Order> orders_;

};

#endif // TASKALLOCATION_H