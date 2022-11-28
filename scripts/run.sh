#!/bin/sh
rosnode kill -a
sleep 5
timestamp=$(date +%s)
roslaunch data_collect main.launch output_dir:="output_"$timestamp