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

unsigned int Order::getPackageNo(void) const
{
    return packageNo_;
}
double Order::getPickUpLoc(void) const
{
    return pickUpLoc_;
}
double Order::getDropOffLoc(void) const
{
    return dropOffLoc_;
}