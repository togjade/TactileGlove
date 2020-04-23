#include <ros/ros.h>
#include <hand_rviz_pub/Raw.h>

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
  int rate = 100;

  // if exactly one arg is supplied, set the rate to it. Otherwise it is 100 HZ
  if(argc == 2)
    rate = atoi(argv[1]);

  ros::Rate loop_rate(rate);
  ros::Publisher chatter_pub = n.advertise<hand_rviz_pub::Raw>("hand/sensors", 1);

  bool dir = true;
  int dirCount = 0;

  // intialize JointState message
  hand_rviz_pub::Raw RawMsg;
  // init the revolutes for fingers
  RawMsg.pressure = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  while (ros::ok()){

    if(dir){

      for(int i = 0; i < 30; i++){

        RawMsg.pressure[i] += 1;
      }
      dirCount++;
      if(dirCount >= 250)
        dir = false;
    }else{

      for(int i = 0; i < 30; i++){

        RawMsg.pressure[i] -= 1;
      }
      dirCount--;
      if(dirCount <= 0)
        dir = true;
    }

    chatter_pub.publish(RawMsg);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
