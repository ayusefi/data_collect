cmake_minimum_required(VERSION 3.13.0)
project(data_collect)

# The package to collect data from different sensors.
# Supported data types:
#   - pointcloud2     saved  ->  timestamp.pcd
#   - Image           saved  ->  timestamp.jpg
#   - Imu             saved  ->  timestamp.txt
#   - Float64         saved  ->  timestamp.txt
#   - NavSatFix       saved  ->  timestamp.txt
#   - Float32Stamped  saved  ->  timestamp.txt
#   - Odometry        saved  ->  timestamp.txt

## Find catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  tf2_ros
  sensor_msgs
  nav_msgs
  rosbag
  ti_mmwave_rospkg
)

## Find system dependencies
find_package(PCL REQUIRED)
find_package( OpenCV REQUIRED )
find_package(Boost REQUIRED COMPONENTS thread filesystem)
message(STATUS ${OpenCV_INCLUDE_DIRS})

include_directories(
  SYSTEM
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

## Declare the catkin package
catkin_package(
  INCLUDE_DIRS include
)

add_executable(pointcloud_saver src/pointcloud_saver_node.cpp src/pointcloud_saver.cpp)
target_link_libraries(pointcloud_saver ${catkin_LIBRARIES} ${PCL_LIBRARIES})
add_dependencies(pointcloud_saver ${catkin_EXPORTED_TARGETS})

add_executable(image_saver src/image_saver_node.cpp src/image_saver.cpp)
target_link_libraries(image_saver ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(image_saver ${catkin_EXPORTED_TARGETS})

add_executable(imu_saver src/imu_saver_node.cpp src/imu_saver.cpp)
target_link_libraries(imu_saver ${catkin_LIBRARIES})
add_dependencies(imu_saver ${catkin_EXPORTED_TARGETS})

add_executable(float64_saver src/float64_saver_node.cpp src/float64_saver.cpp)
target_link_libraries(float64_saver ${catkin_LIBRARIES})
add_dependencies(float64_saver ${catkin_EXPORTED_TARGETS})

add_executable(navsatfix_saver src/navsatfix_saver_node.cpp src/navsatfix_saver.cpp)
target_link_libraries(navsatfix_saver ${catkin_LIBRARIES})
add_dependencies(navsatfix_saver ${catkin_EXPORTED_TARGETS})

add_executable(float32stamped_saver src/float32stamped_saver_node.cpp src/float32stamped_saver.cpp)
target_link_libraries(float32stamped_saver ${catkin_LIBRARIES})
add_dependencies(float32stamped_saver ${catkin_EXPORTED_TARGETS})

add_executable(odometry_saver src/odometry_saver_node.cpp src/odometry_saver.cpp)
target_link_libraries(odometry_saver ${catkin_LIBRARIES})
add_dependencies(odometry_saver ${catkin_EXPORTED_TARGETS})

add_executable(data_to_bag src/data_to_bag_node.cpp src/data_to_bag.cpp)
target_link_libraries(data_to_bag ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(data_to_bag ${catkin_EXPORTED_TARGETS})

add_executable(txt_files_to_list src/txt_files_to_list_node.cpp src/txt_files_to_list.cpp)
target_link_libraries(txt_files_to_list ${catkin_LIBRARIES})
add_dependencies(txt_files_to_list ${catkin_EXPORTED_TARGETS})

add_executable(image_files_to_list src/image_files_to_list_node.cpp src/image_files_to_list.cpp)
target_link_libraries(image_files_to_list ${catkin_LIBRARIES})
add_dependencies(image_files_to_list ${catkin_EXPORTED_TARGETS})

add_executable(pcd_files_to_list src/pcd_files_to_list_node.cpp src/pcd_files_to_list.cpp)
target_link_libraries(pcd_files_to_list ${catkin_LIBRARIES})
add_dependencies(pcd_files_to_list ${catkin_EXPORTED_TARGETS})

add_executable(pcd_files_to_image src/pcd_files_to_image_node.cpp src/pcd_files_to_image.cpp)
target_link_libraries(pcd_files_to_image ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(pcd_files_to_image ${catkin_EXPORTED_TARGETS})

add_executable(ti_radar_saver src/ti_radar_saver_node.cpp src/ti_radar_saver.cpp)
target_link_libraries(ti_radar_saver ${catkin_LIBRARIES})
add_dependencies(ti_radar_saver ${catkin_EXPORTED_TARGETS})