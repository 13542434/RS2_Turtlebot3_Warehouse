#ifndef TURTLEBOT3_H
#define TURTLEBOT3_H

// Define a simple structure for a 2D point (for robot loc)
struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

// TurtleBot3 class definition
class TurtleBot3 {
private:
    Point location; // Current location of the TurtleBot3
    bool hasPackage; // Flag indicating whether the TurtleBot has a package

public:
    // Constructor
    TurtleBot3(double x = 0.0, double y = 0.0, bool hasPackage = false)
        : location(x, y), hasPackage(hasPackage) {}

    // Getters and Setters
    void setLocation(double x, double y) {
        location.x = x;
        location.y = y;
    }

    Point getLocation() const {
        return location;
    }

    void setHasPackage(bool hasPackage) {
        this->hasPackage = hasPackage;
    }

    bool getHasPackage() const {
        return hasPackage;
    }

    // Additional functionality can be added here
};

#endif // TURTLEBOT3_H
