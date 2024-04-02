#ifndef TURTLEBOT3_H
#define TURTLEBOT3_H
#include <vector>

// Define a simple structure for a 2D point (for robot loc)
struct Point {
    double x, y;

    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

// TurtleBot3 class definition
class TurtleBot3 {
private:
    Point location_; // Current location of the TurtleBot3
    bool hasPackage_; // Flag indicating whether the TurtleBot has a package
    std::vector<unsigned int> neighbourhood_; //list of shelf numbers considered part of turtlebot's neighbourhood

public:
    // Constructor
    TurtleBot3();
    TurtleBot3(double x = 0.0, double y = 0.0, bool hasPackage = false);

    // Getters and Setters
    /**
     * Sets the x,y location of turtlebot
    */
    void setLocation(double x, double y);
    /**
     * @return x,y coordinates of turtlebot with reference to global frame
    */
    Point getLocation(void) const;
    /**
     * Sets the hasPackage boolean
    */
    void setHasPackage(bool hasPackage);
    /**
     * @return If the turtlebot has packages to deliver
    */
    bool getHasPackage(void) const;

    // Additional functionality can be added here
    /**
     * @return list of shelf numbers considered part of turtlebot's neighbourhood
    */
    std::vector<unsigned int> getNeighbourhood(void);
};

#endif // TURTLEBOT3_H
