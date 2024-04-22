#include "turtlebot3_warehouse/TurtleBot3Interface.h"
#include "turtlebot3_warehouse/TurtleBot3.h"
#include <fstream>
#include <string>
using namespace std;

TurtleBot3Interface::TurtleBot3Interface(ros::NodeHandle* nh, std::string include_file_path) :
    nh_(*nh), include_file_path_(include_file_path) 
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
        std::cout<<"Created Turtlebot "<<i<<std::endl;
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
    std::ifstream config_file(config_file_path_);
    char myChar;
    std::string myString;
    std::string myText;
    std::string stringToInt;
    bool config_variable_flag = false;
    if (config_file.is_open())
    {
        std::cout<<"config file opened"<<std::endl;
        while (config_file.good())
        {
            std::cout<<"reading config file..."<<std::endl;
            getline(config_file,myText);
            for (auto myChar:myText)
            {
                if (!config_variable_flag)
                {
                    myString += myChar;
                
                    if (myString == config_variable) // read config file number after "NUM_TURTLEBOTS: "
                    {
                        config_variable_flag = true;                    
                    }
                }
                else
                {
                    stringToInt += myChar;
                }
            }
        }
    }
    else
    {
        std::cout<<"config.txt could not be opened"<<std::endl;
    }
    return stoi(stringToInt);
}

