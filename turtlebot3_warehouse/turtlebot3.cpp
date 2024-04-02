#include "turtlebot3.h"

TurtleBot3::TurtleBot3(){

}

TurtleBot3::TurtleBot3(double x = 0.0, double y = 0.0, bool hasPackage = false)
    : location_(x, y), hasPackage_(hasPackage) {}

// Getters and Setters

void TurtleBot3::setLocation(double x, double y) {
    location_.x = x;
    location_.y = y;
}

Point TurtleBot3::getLocation(void) const {
    return location_;
}

void TurtleBot3::setHasPackage(bool hasPackage) {
    this->hasPackage_ = hasPackage;
}

bool TurtleBot3::getHasPackage(void) const {
    return hasPackage_;
}

std::vector<unsigned int> TurtleBot3::getNeighbourhood(void){
    return neighbourhood_;
}