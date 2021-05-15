#!/usr/bin/env bash
echo -----------------------
echo 警告: 
echo 这个启动脚本将会使程序启动至
echo 本地测试模式。
echo 请在生产环境中将其修改为正确的启动文件
echo 然后删除这段警告
echo -----------------------
killall roslaunch
source devel/setup.bash
cp armorboxContours.yml ~/.ros
catkin_make && roslaunch launch/debug_file.launch
