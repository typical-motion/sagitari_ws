#!/usr/bin/env bash
killall roslaunch
source /opt/ros/noetic/setup.zsh
source /opt/ros/noetic/setup.bash
source devel/setup.bash
cp armorboxContours.yml ~/.ros
cp svm2.xml ~/.ros
# catkin_make && roslaunch src/roslaunch.launch
catkin_make && roslaunch launch/sentinel.launch
