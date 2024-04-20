cmake_minimum_required(VERSION 3.0.2)
project(turtlebot3_warehouse)

# Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

# Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  nav_msgs # Assuming you need nav_msgs for your application
)

# Catkin specific configuration
catkin_package(
  # INCLUDE_DIRS include # Uncomment if you have header files in an 'include' directory
  CATKIN_DEPENDS roscpp std_msgs nav_msgs
  # DEPENDS system_lib # Uncomment and list dependencies that are not catkin packages
)

# Specify additional locations of header files
include_directories(
  include # Uncomment if you have an 'include' directory for headers
  ${catkin_INCLUDE_DIRS}
)

# add_executable(multi_bot src/main.cpp src/MultiBot.cpp)
# target_link_libraries(multi_bot ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_node src/main.cpp src/SetGoals.cpp src/MultiBot.cpp src/TurtleBot3.cpp src/TurtleBot3Interface.cpp src/taskallocation.cpp src/order.cpp)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
