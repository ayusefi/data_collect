# data_collect

data_collect is a ROS package to collect data from different sensors. The package was created because:
- The default rosbag tool could not record data for long durations due to buffer limitations. This made the rosbag lose most of the data and sometimes stop recording especially images and point clouds. 
- Also the rosbag takes lots of memory space for a few minutes of data if it contains images/pointclouds (150 GB in 1 hour).
- I observed that the rosbag loses some data while collecting (for example the original sensor data was >400 Hz while the collected data in rosbag was ~380 Hz. 

data_collect is able to collect hours of sensor data with much less space requirement compared to rosbag. The data collected is also suitable for deep learning training/applications with each data having timestamp.

## Features
- Collect data for long durations (Hours).
- Takes much less space compared to rosbag (15% of rosbag).
- No data loss in collected data.
- Collect data from sensors via rostopics.
- Convert collected data back to rosbags and vice versa.
- Convert collected Velodyne pcd files to images.
- Extract list of collected files in csv/txt to be used in deep learning applications.
- Currently supported datatypes:
   - pointcloud2 &emsp; saved &emsp; -> &emsp; timestamp.pcd
   - Image &emsp; saved &emsp; -> &emsp; timestamp.jpg
   - Imu &emsp; saved &emsp; -> &emsp; Imu.txt
   - Float64 &emsp; saved &emsp; -> &emsp; float64.txt
   - NavSatFix &emsp; saved &emsp; -> &emsp; fix.txt
   - Float32Stamped &emsp; saved &emsp; -> &emsp; float32stamped.txt
   - Odometry &emsp; saved &emsp; -> &emsp; odom.txt
   - ti_mmwave radar &emsp; saved &emsp; -> &emsp; ti_mmwave.txt

## Usage
Clone the package into your workspace and catkin_make it.
```bash
mkdir -p data_collect_ws/src
cd data_collect_ws/src
git clone git@github.com:ayusefi/data_collect.git
cd ..
catkin_make
source devel/setup.bash
```

### Collect Data

In **main.launch** edit the **output directory**, and **topic names**. An example of each sensor type is given in the file.
```xml
	<!-- velodyne -->
	<node pkg="data_collect" type="pointcloud_saver" name="pointcloud_saver_velodyne_node" output="screen" clear_params="true">
		<param name="pointcloud_topic" type="string" value="/velodyne_points" />
		<param name="output_path" type="string" value="$(arg output_dir)/velodyne/" />
	</node>

	<!-- zed_camera -->
	<node pkg="data_collect" type="image_saver" name="image_saver_node" output="screen" clear_params="true">
		<param name="image_topic" type="string" value="/zed/zed_node/right_raw/image_raw_color" />
		<param name="output_path" type="string" value="$(arg output_dir)/image/" />
	</node>

	<!-- imu -->
	<node pkg="data_collect" type="imu_saver" name="imu_saver_node" output="screen" clear_params="true">
		<param name="imu_topic" type="string" value="/imu/data" />
		<param name="output_path" type="string" value="$(arg output_dir)/imu/" />
	</node>
```
Run the main.launch file.

```bash
roslaunch data_collect main.launch
```

### Convert collected data bag to rosbag
In **data_to_bag.launch** edit the **output directory (path to collected data)**, **directory_names**, **topic_names**, **frame_ids**, **data_types**. An example of each sensor type is given in the file. The **output.bag** will be saved in output directory. _Remeber, the order of parameters is important._
```xml
<launch>
	<arg name="output_dir" default="/home/oem/output_test/"/>

	<node pkg="data_collect" type="data_to_bag" name="data_to_bag_node" output="screen" clear_params="true">
		<param name="dataset_path" type="string" value="$(arg output_dir)" />
		<rosparam param="directory_names">["fix","image","imu","odometry_filtered","radar","velodyne","zed_odom"]</rosparam>
		<rosparam param="topic_names">["/fix","/zed/zed_node/right_raw/image_raw_color","/imu/data","/odometry/filtered","/radar/target_list_cartesian","/velodyne_points","/zed/zed_node/odom"]</rosparam>
		<rosparam param="frame_ids">["gps","zed","imu","odometry_filtered","smart_micro","velodyne","zed_odom"]</rosparam>
		<rosparam param="data_types">["NavSatFix","Image","Imu","Odometry","PointCloud2","PointCloud2","Odometry"]</rosparam>
	</node>
</launch>
```

Run the **data_to_bag.launch** file.
```bash
roslaunch data_collect data_to_bag.launch
```

### Extract list of images and pcd files
In **files_to_list.launch**, edit and add **output directory** and **nodes** as per your collected data. An example of each sensor type is given in the file.
```xml
	<arg name="output_dir" default="/home/oem/output_test"/>

	<!-- image -->
	<node pkg="data_collect" type="image_files_to_list" name="image_files_to_list_node" output="screen" clear_params="true">
		<param name="directory_path" type="string" value="$(arg output_dir)/image" />
	</node>

	<!-- velodyne -->
	<node pkg="data_collect" type="pcd_files_to_list" name="pcd_files_to_list_velodyne_node" output="screen" clear_params="true">
		<param name="directory_path" type="string" value="$(arg output_dir)/velodyne" />
	</node>
```

Run the **files_to_list.launch** file.
```bash
roslaunch data_collect files_to_list.launch
```

### Convert velodyne pcd files to images.
In **pcd_files_to_image.launch** edit the output directory path.
```xml
	<arg name="output_dir" default="/home/oem/output_test"/>

	<!-- velodyne -->
	<node pkg="data_collect" type="pcd_files_to_image" name="pcd_files_to_image_velodyne_node" output="screen" clear_params="true">
		<param name="directory_path" type="string" value="$(arg output_dir)/velodyne" />
	</node>
```
Run the **pcd_files_to_image.launch** file.
```bash
roslaunch data_collect pcd_files_to_image.launch
```

