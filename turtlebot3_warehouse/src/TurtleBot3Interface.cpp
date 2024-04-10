#include "turtlebot3_warehouse/TurtleBot3Interface.h"
#include "turtlebot3_warehouse/TurtleBot3.h"
#include <fstream>
#include <string>
using namespace std;

TurtleBot3Interface::TurtleBot3Interface(ros::NodeHandle* nh) :
    nh_(*nh) 
{
    // create the number of turtlebots given in config.txt
    num_turtlebots_ = configSearch("NUM_TURTLEBOTS: ");
    
    // make turtlebots
    std::string topic_string;
    int topic_num;
    for (int i = 0; i < num_turtlebots_; i++)
    {
        // create the topic_string_ in the form of "/tb3_#/amcl_pose" where # is starting from 0 and ends in i-1
        topic_num = i;
        topic_string = "/tb3_" + to_string(topic_num) + "/amcl_pose";
        turtlebots_.push_back(new TurtleBot3(&nh_, topic_string));
    }
    
    
}

std::vector<TurtleBot3*> TurtleBot3Interface::getTurtleBotsList(void)
{
    return turtlebots_;
}

int TurtleBot3Interface::getNumTurtlebots(void)
{
    return num_turtlebots_;
}

int TurtleBot3Interface::configSearch(std::string config_variable) {
    std::ifstream config_file("../config.txt");
    char myChar;
    std::string myString;
    std::string stringToInt;
    if (config_file.is_open())
    {
        while (config_file)
        {
            myChar = config_file.get();
            if (myChar != '\n')
            {
                myString += myChar;
            }
            else
            {
                myString.clear();
            }
            
            if (myString == config_variable) // read config file number after "NUM_TURTLEBOTS: "
            {
                while (myChar != '\n')
                {
                    myChar = config_file.get();
                    stringToInt += myChar;
                }
                return stoi(stringToInt);
            }
        }
    }
}

