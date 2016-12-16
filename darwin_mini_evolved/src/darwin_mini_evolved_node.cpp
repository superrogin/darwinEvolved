#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "darwin_mini_evolved_node");
	ros::NodeHandle nh;
	ros::Publisher dme_test_pub = nh.advertise<std_msgs::String>("dme_test_msg",10);
	ros::Rate loop_rate(100);
	
	std_msgs::String msg;
	std::stringstream ss;
	ss << "darwin mini evolved node started";
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());
	
	dme_test_pub.publish(msg);

	while(ros::ok())
	{
		


		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
	
}