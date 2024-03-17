Add these files into ~/catkin_ws/src
1. Compile your workspace
    NOTE: if using VMware, you may need to run (export SVGA_VGPU10=0 in addition to fix 3D acceleration/GPU passthrough)
3. export TURTLEBOT3_MODEL=waffle_pi
4. roslaunch turtlebot3_gazebo multi_turtlebot3.launch
6. New terminal, export TURTLEBOT3_MODEL=waffle_pi
7. cd ~/catkin_ws$
8. source devel/setup.bash
9. roslaunch turtlebot3_navigation multi_nav_bringup.launch
10. cd ~/catkin_ws/src/multi_turtlebot3/scripts$
11. Enter the following without quotations to execute python script "./publish_goal.py"
12. Goals should be published to 2/3 of the turtlebots in the world.
13. Running "./plan_length.py" will output the length of the current planned path (for tb3_0, the first turtlebot)
