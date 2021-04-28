#!/usr/bin/env bash
source devel/setup.bash
catkin_make
cp armorboxContours.yml ~/.ros
roslaunch src/roslaunch.launch