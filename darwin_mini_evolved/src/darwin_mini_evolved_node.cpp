#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

char device[]= "/dev/ttyACM0";

int fd;

unsigned long baud = 19200;
unsigned long waitingTime = 0;

const int numJoint = 16;

void setup(void);
void loop(void);
void moveAlljoints(int value);

void setup(){

	printf("%s \n", "Raspberry Startup!");
	fflush(stdout);

	if ((fd = serialOpen (device, baud)) < 0) {
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno));
		exit(1);
	}

	if (wiringPiSetup () == -1) {
		fprintf (stdout, "unable to start wiringPi : %s\n", strerror (errno));
		exit(1);
	}
}

void moveAlljoints(int value) {
	char strSend[numJoint*2+3];
	strSend[0] = 's';
	strSend[numJoint*2+1] = 'e';
	int high = value/32 + 200;
	int low = value%32 + 200;
	for (int i = 0; i<numJoint; i++)
	{
		strSend[i*2+1] = high;
		strSend[i*2+2] = low;
	}

	serialPuts(fd,strSend);
	ros::NodeHandle nh;
	ros::Publisher dme_test_pub = nh.advertise<std_msgs::String>("dme_test_msg",10);
	std_msgs::String msg;
	std::stringstream ss;
	ss << strSend;
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());
	
	dme_test_pub.publish(msg);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "darwin_mini_evolved_node");
	ros::NodeHandle nh;
	ros::Publisher dme_test_pub = nh.advertise<std_msgs::String>("dme_test_msg",10);
	ros::Rate loop_rate(1);
	
	std_msgs::String msg;
	std::stringstream ss;
	ss << "darwin mini evolved node started";
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());
	
	dme_test_pub.publish(msg);

	setup();
	int a = 30;
	while(ros::ok())
	{
		moveAlljoints(512 + a);
		a = -a;

		//if(millis()-time>=3000) {
		//serialPutchar (fd,1);
		//time=millis();

		//while(millis()-time<3000) {
		//}
		//	serialPutchar(fd,250);
		//	time = millis();
		//}
	
		//if (serialDataAvail (fd)) {
		//	char newChar = serialGetchar (fd);
		//	printf("%c", newChar);
		//	fflush(stdout);
		//}

		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
	
}