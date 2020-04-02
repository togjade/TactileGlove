#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

// advised finger rotation limits; in radians
// finger1 limits
#define F1AMIN -0.15
#define F1AMAX 0.96
#define F1BMIN -2.0
#define F1BMAX -0.89
// finger2 limits
#define F2AMIN -0.44
#define F2AMAX 0.67
#define F2BMIN -0.31
#define F2BMAX 0.8
// finger3 limits
#define F3AMIN -0.23
#define F3AMAX 0.88
#define F3BMIN -0.23
#define F3BMAX 0.88
// finger4 limits
#define F4AMIN -0.03
#define F4AMAX 1.08
#define F4BMIN -0.09
#define F4BMAX 1.02
// thumb limits
#define TAMIN 0
#define TAMAX 0.1
#define TCMIN -0.6
#define TCMAX -0.31


// example publisher for talker3. Sends JointState message
int main(int argc, char **argv){

  ros::init(argc, argv, "talker4");
  ros::NodeHandle n;
  int rate = 10;

  // if exactly one arg is supplied, set the rate to it. Otherwise it is 10 HZ
  if(argc == 2)
    rate = atoi(argv[1]);

  ros::Rate loop_rate(rate);
  ros::Publisher chatter_pub = n.advertise<sensor_msgs::JointState>("hand/sensors", 1);

  double count1a = F1AMIN;
  double count1b = F1BMIN;
  double count2a = F2AMIN;
  double count2b = F2BMIN;
  double count3a = F3AMIN;
  double count3b = F3BMIN;
  double count4a = F4AMIN;
  double count4b = F4BMIN;
  double count0a = TAMIN;
  double count0c = TCMIN;
  bool dir = true;
  double c0ach = 0.0001/1.11;
  double c0cch = 0.0029/1.11;

  // intialize JointState message
  sensor_msgs::JointState jointMsg;
  jointMsg.header.seq = 0;
  jointMsg.header.frame_id = "";
  // init the revolutes for fingers
  jointMsg.name = {"finger1a", "finger1b", "finger2a", "finger2b", "finger3a", "finger3b", "finger4a", "finger4b", "thumba", "thumbc"};

  while (ros::ok()){

    jointMsg.header.stamp = ros::Time();
    jointMsg.position = {count1a, count1b, count2a, count2b, count3a, count3b, count4a, count4b, count0a, count0c};

    if(dir){

      count1a += 0.01;
      count1b += 0.01;
      count2a += 0.01;
      count2b += 0.01;
      count3a += 0.01;
      count3b += 0.01;
      count4a += 0.01;
      count4b += 0.01;
      count0a += c0ach;
      count0c += c0cch;
      if(count1a >= F1AMAX)
        dir = false;
    }else{

      count1a -= 0.01;
      count1b -= 0.01;
      count2a -= 0.01;
      count2b -= 0.01;
      count3a -= 0.01;
      count3b -= 0.01;
      count4a -= 0.01;
      count4b -= 0.01;
      count0a -= c0ach;
      count0c -= c0cch;
      if(count1a <= F1AMIN)
        dir = true;
    }

    chatter_pub.publish(jointMsg);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
