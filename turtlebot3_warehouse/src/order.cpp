#include "turtlebot3_warehouse/order.h"

Order::Order(std::string include_file_path) : 
    include_file_path_(include_file_path)
{}

Order::Order(std::string include_file_path, unsigned int packageNo, unsigned int pickUpLoc, unsigned int dropOffLoc):
include_file_path_(include_file_path), packageNo_(packageNo), pickUpLoc_(pickUpLoc), dropOffLoc_(dropOffLoc)
{
    std::vector<double> coords_ = getCoordinates(pickUpLoc_);
}

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

std::vector<double> Order::getCoordinates(unsigned int location)
{
    std::vector<double> coords;
    std::ifstream adresses_file(adresses_file_path_);
    std::string myText;
    unsigned int addressState = 0;
    int counter = -1;
    int packageNum = 0;
    std::string packageNum_str;
    int xCoord = 0;
    std::string xCoord_str;
    int yCoord = 0;
    std::string yCoord_str;

    if (adresses_file.is_open())
    {
        std::cout << "package_orders.csv reads:" << std::endl;
        while (adresses_file.good()) { 
            getline(adresses_file, myText);
            std::cout << myText << std::endl;
            addressState = 0;
            
            if (counter >= 0) // skip first line (locationNo,xCoord,yCoord)
            {
                for (auto myChar:myText)
                {
                    switch (addressState)
                    {
                    case 0:
                        // all characters until next comma are the packageNum
                        if (myChar == ',')
                        {
                            packageNum = stoi(packageNum_str);
                            addressState++;
                            packageNum_str = "";
                        }
                        else
                        {
                            packageNum_str += myChar;
                        }                        
                        break;
                    case 1:
                        // all characters until next comma are the xCoord
                        if (myChar == ',')
                        {
                            xCoord = stoi(xCoord_str);
                            addressState++;
                            xCoord_str = "";
                        }
                        else
                        {
                            xCoord_str += myChar;
                        }
                        break;
                    case 2:
                        // all characters until next comma are the yCoord
                        if (myChar == ',')
                        {
                            yCoord = stoi(yCoord_str);
                            addressState = 0;
                            yCoord_str = "";
                        }
                        else
                        {
                           yCoord_str += myChar;
                        }
                        break;
                    default:
                        break;                        
                    }

                }            

                if (packageNo_ == packageNum)
                {
                    coords_.at(1) = xCoord;
                    coords_.at(2) = yCoord;
                    break;
                }
                
                packageNum = 0;
                xCoord = 0;
                yCoord = 0;
            }
            counter++;
            
        }        
    }
    else
    {
        std::cout << "package_orders.csv could not be read" <<std::endl;
    }  

    std::cout << "Coords are:" << coords.at(1) << ", " << coords.at(2) << std::endl;

    return coords;
}