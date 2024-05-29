Add these files into ~/catkin_ws/src
1. Delete the build folder
2. Edit main.cpp variable include_file_path to use your own file path to the include folder
3. If changing the number of turtlebots do so in the launch file AND the config.txt file in include/turtlebot3_warehouse
4. Compile your workspace
    NOTE: if using VMware, you may need to run (export SVGA_VGPU10=0 in addition to fix 3D acceleration/GPU passthrough)
5. export TURTLEBOT3_MODEL=waffle_pi
6. roslaunch turtlebot3_gazebo multi_turtlebot3.launch
7. New terminal, export TURTLEBOT3_MODEL=waffle_pi
8. cd ~/catkin_ws$
9. catkin_make
10. source devel/setup.bash
11. roslaunch turtlebot3_navigation multi_nav_bringup.launch

12. You can run the code in VSCODE (open folder ~/catkin_ws/src/turtlebot3_warehouse/src) 
		OR
	rosrun turtlebot3_warehouse turtlebot3_warehouse_node

lkh python library must be installed for the TSP solver to work: https://pypi.org/project/lkh/
/
/
/
/
/ 
///////////////

General Notes:

calculateLivePlans uses /move_base/make_plan and calculates plans to all packages based on current locations of the robots (amcl pose)
calculateFuturePlanc calculates plans to all packages between other packages.

Basic data is outputted into plans.csv and commandline. This can be changed later to increase detail (can easily add coordinates if you need, i took them out for simplicity for now)

SetGoals is currently not used, but the implementation works. This will be useful a bit later.

I could not get namspaces workign with TurtleBot3.h etc. so that you can instantiate the class multiple times in MultiBot.h.
At the moment, if you look in the class you will see that i have just got multiple data for each turtlebot, not multiple classes.
This will also need to be done for indicating if a turtlebot has the package or not, but I think this approach should work for now?
/



/
/
/
//////////////////////

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
10. cd ~/catkin_ws/src/multi_turtlebot3/scripts$
11. Enter the following without quotations to execute python script "./publish_goal.py"
12. Goals should be published to 2/3 of the turtlebots in the world.
13. Running "./plan_length.py" will output the length of the current planned path (for tb3_0, the first turtlebot)

If you want to cancel at any time, you can publish  rostopic pub /tb3_0/move_base/cancel actionlib_msgs/GoalID "{}"
or subsequient /tb3_x/

example make_plan publisher (visualises on map) 
rosservice call /tb3_0/move_base/make_plan "start:
  header:
    frame_id: 'map'
  pose:
    position:
      x: 0.5
      y: 3.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
goal:
  header:
    frame_id: 'map'
  pose:
    position:
      x: 6.0
      y: -2.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
tolerance: 0.5"

