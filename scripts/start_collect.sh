#!/bin/sh
roslaunch golf_araba m4k.launch
# sleep 10
timestamp=$(date +%s)
roslaunch data_collect main.launch output_dir:="output_"$timestamp
