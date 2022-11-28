#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

class VelodynePointcloudToDepthimage{
	private:
		/*node handle*/
		ros::NodeHandle _nh;
		ros::NodeHandle _nhPrivate;
		/*subscriber*/
		ros::Subscriber _sub_pc;
		/*publisher*/
		ros::Publisher _pub_img_64f;
		/*image*/
		cv::Mat _img_cv_64f;
		/*point cloud*/
		std::vector<pcl::PointCloud<pcl::PointXYZI>::Ptr> _rings;
		/*parameter*/
		int _num_ring;
		int _points_per_ring;

	public:
		VelodynePointcloudToDepthimage();
		void callbackPC(const sensor_msgs::PointCloud2ConstPtr& msg);
		void pcToRings(const sensor_msgs::PointCloud2& pc_msg);
		void ringsToImage(void);
		void publication(std_msgs::Header header);
};

VelodynePointcloudToDepthimage::VelodynePointcloudToDepthimage()
	: _nhPrivate("~")
{
	std::cout << "--- velodyne_pointcloud_to_depthimage ---" << std::endl;
	/*parameter*/
	_nhPrivate.param("num_ring", _num_ring, 16);
	std::cout << "_num_ring = " << _num_ring << std::endl;
	_nhPrivate.param("points_per_ring", _points_per_ring, 897);
	std::cout << "_points_per_ring = " << _points_per_ring << std::endl;
	/*subscriber*/
	_sub_pc = _nh.subscribe("/velodyne_points", 1, &VelodynePointcloudToDepthimage::callbackPC, this);
	/*publisher*/
	_pub_img_64f = _nh.advertise<sensor_msgs::Image>("/depth_image/64fc1", 1);
	/*initialize*/
	_rings.resize(_num_ring);
	for(size_t i=0 ; i<_rings.size() ; ++i){
		pcl::PointCloud<pcl::PointXYZI>::Ptr tmp (new pcl::PointCloud<pcl::PointXYZI>);
		_rings[i] = tmp;
	}
}

void VelodynePointcloudToDepthimage::callbackPC(const sensor_msgs::PointCloud2ConstPtr &msg)
{
	for(size_t i=0 ; i<_rings.size() ; ++i){
		_rings[i]->points.clear();
	}
	pcToRings(*msg);
	ringsToImage();
	publication(msg->header);
}

void VelodynePointcloudToDepthimage::pcToRings(const sensor_msgs::PointCloud2& pc_msg)
{
	sensor_msgs::PointCloud2ConstIterator<uint16_t> iter_ring(pc_msg,"ring");
	sensor_msgs::PointCloud2ConstIterator<float> iter_x(pc_msg,"x");
	sensor_msgs::PointCloud2ConstIterator<float> iter_y(pc_msg,"y");
	sensor_msgs::PointCloud2ConstIterator<float> iter_z(pc_msg,"z");
	sensor_msgs::PointCloud2ConstIterator<float> iter_intensity(pc_msg,"intensity");

	for( ; iter_ring!=iter_ring.end() ; ++iter_ring, ++iter_x, ++iter_y, ++iter_z, ++iter_intensity){
		pcl::PointXYZI tmp;
		tmp.x = *iter_x;
		tmp.y = *iter_y;
		tmp.z = *iter_z;
		tmp.intensity = *iter_intensity;
		_rings[*iter_ring]->points.push_back(tmp);
	}
}

void VelodynePointcloudToDepthimage::ringsToImage(void)
{
	/*reset*/
	_img_cv_64f = cv::Mat::zeros(_num_ring, _points_per_ring, CV_64FC1);
	/*input*/
	double angle_resolution = 2*M_PI/(double)_points_per_ring;
	for(size_t i=0 ; i<_rings.size() ; ++i){
		int row = _rings.size() - i - 1;
		for(size_t j=0 ; j<_rings[i]->points.size() ; ++j){
			double angle = atan2(_rings[i]->points[j].y, _rings[i]->points[j].x);
			int col = _points_per_ring - (int)((angle + M_PI)/angle_resolution) - 1;
			_img_cv_64f.at<double>(row, col) = sqrt(_rings[i]->points[j].x*_rings[i]->points[j].x + _rings[i]->points[j].y*_rings[i]->points[j].y);
      // cv::imwrite("/home/oem/workspaces/data_collect_ws/test.png", _img_cv_64f);
		}
	}
}

void VelodynePointcloudToDepthimage::publication(std_msgs::Header header)
{
  _img_cv_64f.convertTo(_img_cv_64f, CV_8UC1);
	sensor_msgs::ImagePtr img_ros_64f = cv_bridge::CvImage(header, "8UC1", _img_cv_64f).toImageMsg();
	_pub_img_64f.publish(img_ros_64f);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "velodyne_pointcloud_to_depthimage");
	
	VelodynePointcloudToDepthimage velodyne_pointcloud_to_depthimage;

	ros::spin();
}