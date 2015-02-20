// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <sstream>


int main (int argc, char** argv)
{

		boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer_final(new pcl::visualization::PCLVisualizer);
  // Create a ROS subscriber for the input point cloud
		
        //viewer_final->addPointCloud<pcl::PointXYZ>(lastCloud.makeShared(), lastCloudHandler,"last");

        //viewer_final->addPointCloud<pcl::PointXYZ>(currentCloud.makeShared(), currentCloudHandler,  "current");



        
        viewer_final->spin();
    
    
}
