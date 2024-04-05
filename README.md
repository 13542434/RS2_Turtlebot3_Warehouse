Add these files into ~/catkin_ws/src
1. Compile your workspace
    NOTE: if using VMware, you may need to run (export SVGA_VGPU10=0 in addition to fix 3D acceleration/GPU passthrough)
3. export TURTLEBOT3_MODEL=waffle_pi
4. roslaunch turtlebot3_gazebo multi_turtlebot3.launch
6. New terminal, export TURTLEBOT3_MODEL=waffle_pi
7. cd ~/catkin_ws$
8. catkin_make
9. source devel/setup.bash
10. roslaunch turtlebot3_navigation multi_nav_bringup.launch

11. IMPORTANT: GO INTO THE CODE AND UPDATE THE PATHS IN MultiBot.cpp!!!
e.g std::ofstream file("/home/nk/catkin_ws/src/turtlebot3_warehouse/src/plans.csv");
Update in void loadPackages, calculateFuturePlans, calculateLivePlans
You may also need to update cmake lists directories

13. You can run the code in VSCODE (open folder ~/catkin_ws/src/turtlebot3_warehouse/src) 
		OR
	rosrun turtlebot3_warehouse turtlebot3_warehouse_node


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

