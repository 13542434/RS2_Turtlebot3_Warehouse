Add these files into ~/catkin_ws/src
1. Delete the build folder
2. Edit main.cpp variable include_file_path to use your own file path to the include folder
3. If changing the number of turtlebots do so in the launch file AND the config.txt file in include/turtlebot3_warehouse
4. Compile your workspace
    NOTE: if using VMware, you may need to run (export SVGA_VGPU10=0 in addition to fix 3D acceleration/GPU passthrough)
5. export TURTLEBOT3_MODEL=waffle_pi
6. roslaunch turtlebot3_navigation multi_turtlebot3.launch world_file:=/YOUR PATH/catkin_ws/src/multi_turtlebot3/turtlebot3_navigation/worlds/rs2warehouse.world
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
