#!/usr/bin/env bash
source devel/setup.bash
cp armorboxContours.yml ~/.ros
catkin_make && roslaunch src/roslaunch.launch
