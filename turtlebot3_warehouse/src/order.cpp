#include "turtlebot3_warehouse/order.h"

Order::Order()
{}

Order::Order(unsigned int packageNo, unsigned int pickUpLoc, unsigned int dropOffLoc):
packageNo_(packageNo), pickUpLoc_(pickUpLoc), dropOffLoc_(dropOffLoc)
{}

void Order::setPackageNo(unsigned int packageNo)
{
    packageNo_ = packageNo;
}
void Order::setPickUpLoc(unsigned int pickUpLoc)
{
    pickUpLoc_ = pickUpLoc;
}
void Order::setDropOffLoc(unsigned int dropOffLoc)
{
    dropOffLoc_ = dropOffLoc;
}  

unsigned int Order::getPackageNo(void)
{
    return packageNo_;
}
unsigned int Order::getPickUpLoc(void)
{
    return pickUpLoc_;
}
unsigned int Order::getDropOffLoc(void)
{
    return dropOffLoc_;
}