#ifndef ORDER_H
#define ORDER_H

#include <vector>

// Include any other header files this class relies on

class Order
{
public:
    // Default Constructors
    Order();
    Order(unsigned int packageNo, unsigned int pickUpLoc, unsigned int dropOffLoc);

    void setPackageNo(unsigned int packageNo);
    void setPickUpLoc(unsigned int pickUpLoc);
    void setDropOffLoc(unsigned int dropOffLoc);    

    unsigned int getPackageNo(void);
    unsigned int getPickUpLoc(void);
    unsigned int getDropOffLoc(void);
    
protected:

private:
    // Functionality not used elsewhere goes here
    unsigned int packageNo_;
    unsigned int pickUpLoc_;
    unsigned int dropOffLoc_;
};
#endif // ORDER_H