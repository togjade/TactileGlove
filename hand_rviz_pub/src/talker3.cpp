#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

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

// Marker props
#define XPOS 0
#define YPOS 0.025
#define ZPOS 0
#define SCALE 0.008
#define ACOL 1.0
#define RCOL 0.0
#define GCOL 1.0
#define BCOL 0.0

// declare JointState message
sensor_msgs::JointState jointMsg;
// declare MarkerArray
visualization_msgs::MarkerArray markerMsgs;

// pub pointers
ros::Publisher *pubPtr1;
ros::Publisher *pubPtr2;

// callback to manage anlgles and markers. WIP; need to choose suitable message type; for now using JointState
void sensorsCallback(const sensor_msgs::JointState::ConstPtr& msg);

// subscriber version
int main(int argc, char **argv){

  ros::init(argc, argv, "talker3");
  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<sensor_msgs::JointState>("hand/joint_states", 1);
  ros::Publisher chatter_pub2 = n.advertise<visualization_msgs::MarkerArray>("hand/markers_array", 1);

  // initialize the pointers to the pubs
  pubPtr1 = &chatter_pub;
  pubPtr2 = &chatter_pub2;

  // initialize JointState message
  jointMsg.header.seq = 0;
  jointMsg.header.frame_id = "";
  // init the revolutes for fingers
  jointMsg.name = {"finger1a", "finger1b", "finger2a", "finger2b", "finger3a", "finger3b", "finger4a", "finger4b", "thumba", "thumbc"};
  // initialize MarkerArray
  markerMsgs.markers.resize(27);

  // initialize sensor markers on the first finger
  // initialize first Marker message
  markerMsgs.markers[0].header.frame_id = "finger1_middle";
  markerMsgs.markers[0].ns = "my_namespace";
  markerMsgs.markers[0].id = 0;
  markerMsgs.markers[0].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[0].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[0].pose.position.x = XPOS-0.016;
  markerMsgs.markers[0].pose.position.y = YPOS-0.012;
  markerMsgs.markers[0].pose.position.z = ZPOS+0.025;
  markerMsgs.markers[0].pose.orientation.x = -0.05;
  markerMsgs.markers[0].pose.orientation.y = 0;
  markerMsgs.markers[0].pose.orientation.z = 0;
  markerMsgs.markers[0].pose.orientation.w = 0.998749217;
  markerMsgs.markers[0].scale.z = SCALE;
  markerMsgs.markers[0].scale.x = SCALE;
  markerMsgs.markers[0].scale.y = SCALE;
  markerMsgs.markers[0].color.a = ACOL;
  markerMsgs.markers[0].color.r = RCOL;
  markerMsgs.markers[0].color.g = GCOL;
  markerMsgs.markers[0].color.b = BCOL;
  markerMsgs.markers[0].lifetime = ros::Duration();

  // initialize second Marker message
  markerMsgs.markers[1].header.frame_id = "finger1_middle";
  markerMsgs.markers[1].ns = "my_namespace";
  markerMsgs.markers[1].id = 1;
  markerMsgs.markers[1].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[1].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[1].pose.position.x = XPOS-0.016;
  markerMsgs.markers[1].pose.position.y = YPOS-0.012;
  markerMsgs.markers[1].pose.position.z = ZPOS+0.049;
  markerMsgs.markers[1].pose.orientation.x = -0.05;
  markerMsgs.markers[1].pose.orientation.y = 0;
  markerMsgs.markers[1].pose.orientation.z = 0;
  markerMsgs.markers[1].pose.orientation.w = 0.998749217;
  markerMsgs.markers[1].scale.z = SCALE;
  markerMsgs.markers[1].scale.x = SCALE;
  markerMsgs.markers[1].scale.y = SCALE;
  markerMsgs.markers[1].color.a = ACOL;
  markerMsgs.markers[1].color.r = RCOL;
  markerMsgs.markers[1].color.g = GCOL;
  markerMsgs.markers[1].color.b = BCOL;
  markerMsgs.markers[1].lifetime = ros::Duration();

  // initialize third Marker message
  markerMsgs.markers[2].header.frame_id = "finger1_tip";
  markerMsgs.markers[2].ns = "my_namespace";
  markerMsgs.markers[2].id = 2;
  markerMsgs.markers[2].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[2].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[2].pose.position.x = XPOS-0.016;
  markerMsgs.markers[2].pose.position.y = YPOS-0.025+0.015;
  markerMsgs.markers[2].pose.position.z = ZPOS-0.017;
  markerMsgs.markers[2].pose.orientation.x = -0.25;
  markerMsgs.markers[2].pose.orientation.y = 0;
  markerMsgs.markers[2].pose.orientation.z = 0;
  markerMsgs.markers[2].pose.orientation.w = 0.968245836;
  markerMsgs.markers[2].scale.z = SCALE;
  markerMsgs.markers[2].scale.x = SCALE;
  markerMsgs.markers[2].scale.y = SCALE;
  markerMsgs.markers[2].color.a = ACOL;
  markerMsgs.markers[2].color.r = RCOL;
  markerMsgs.markers[2].color.g = GCOL;
  markerMsgs.markers[2].color.b = BCOL;
  markerMsgs.markers[2].lifetime = ros::Duration();

  // initialize sensor markers on the second finger
  // initialize first Marker message
  markerMsgs.markers[3].header.frame_id = "finger2_middle";
  markerMsgs.markers[3].ns = "my_namespace";
  markerMsgs.markers[3].id = 3;
  markerMsgs.markers[3].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[3].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[3].pose.position.x = XPOS-0.039;
  markerMsgs.markers[3].pose.position.y = YPOS-0.004;
  markerMsgs.markers[3].pose.position.z = ZPOS+0.025;
  markerMsgs.markers[3].pose.orientation.x = -0.2;
  markerMsgs.markers[3].pose.orientation.y = 0;
  markerMsgs.markers[3].pose.orientation.z = 0;
  markerMsgs.markers[3].pose.orientation.w = 0.979795897;
  markerMsgs.markers[3].scale.z = SCALE;
  markerMsgs.markers[3].scale.x = SCALE;
  markerMsgs.markers[3].scale.y = SCALE;
  markerMsgs.markers[3].color.a = ACOL;
  markerMsgs.markers[3].color.r = RCOL;
  markerMsgs.markers[3].color.g = GCOL;
  markerMsgs.markers[3].color.b = BCOL;
  markerMsgs.markers[3].lifetime = ros::Duration();

  // initialize second Marker message
  markerMsgs.markers[4].header.frame_id = "finger2_middle";
  markerMsgs.markers[4].ns = "my_namespace";
  markerMsgs.markers[4].id = 4;
  markerMsgs.markers[4].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[4].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[4].pose.position.x = XPOS-0.039;
  markerMsgs.markers[4].pose.position.y = YPOS+0.002;
  markerMsgs.markers[4].pose.position.z = ZPOS+0.045;
  markerMsgs.markers[4].pose.orientation.x = -0.2;
  markerMsgs.markers[4].pose.orientation.y = 0;
  markerMsgs.markers[4].pose.orientation.z = 0;
  markerMsgs.markers[4].pose.orientation.w = 0.979795897;
  markerMsgs.markers[4].scale.z = SCALE;
  markerMsgs.markers[4].scale.x = SCALE;
  markerMsgs.markers[4].scale.y = SCALE;
  markerMsgs.markers[4].color.a = ACOL;
  markerMsgs.markers[4].color.r = RCOL;
  markerMsgs.markers[4].color.g = GCOL;
  markerMsgs.markers[4].color.b = BCOL;
  markerMsgs.markers[4].lifetime = ros::Duration();

  // initialize third Marker message
  markerMsgs.markers[5].header.frame_id = "finger2_tip";
  markerMsgs.markers[5].ns = "my_namespace";
  markerMsgs.markers[5].id = 5;
  markerMsgs.markers[5].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[5].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[5].pose.position.x = XPOS-0.039;
  markerMsgs.markers[5].pose.position.y = YPOS-0.008;
  markerMsgs.markers[5].pose.position.z = ZPOS+0.01;
  markerMsgs.markers[5].pose.orientation.x = -0.35;
  markerMsgs.markers[5].pose.orientation.y = 0;
  markerMsgs.markers[5].pose.orientation.z = 0;
  markerMsgs.markers[5].pose.orientation.w = 0.936749699;  
  markerMsgs.markers[5].scale.z = SCALE;
  markerMsgs.markers[5].scale.x = SCALE;
  markerMsgs.markers[5].scale.y = SCALE;
  markerMsgs.markers[5].color.a = ACOL;
  markerMsgs.markers[5].color.r = RCOL;
  markerMsgs.markers[5].color.g = GCOL;
  markerMsgs.markers[5].color.b = BCOL;
  markerMsgs.markers[5].lifetime = ros::Duration();

  // initialize sensor markers on the third finger
  // initialize first Marker message
  markerMsgs.markers[6].header.frame_id = "finger3_middle";
  markerMsgs.markers[6].ns = "my_namespace";
  markerMsgs.markers[6].id = 6;
  markerMsgs.markers[6].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[6].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[6].pose.position.x = XPOS-0.063;
  markerMsgs.markers[6].pose.position.y = YPOS-0.01;
  markerMsgs.markers[6].pose.position.z = ZPOS+0.025;
  markerMsgs.markers[6].pose.orientation.x = -0.1;
  markerMsgs.markers[6].pose.orientation.y = 0;
  markerMsgs.markers[6].pose.orientation.z = 0;
  markerMsgs.markers[6].pose.orientation.w = 0.994987437;
  markerMsgs.markers[6].scale.z = SCALE;
  markerMsgs.markers[6].scale.x = SCALE;
  markerMsgs.markers[6].scale.y = SCALE;
  markerMsgs.markers[6].color.a = ACOL;
  markerMsgs.markers[6].color.r = RCOL;
  markerMsgs.markers[6].color.g = GCOL;
  markerMsgs.markers[6].color.b = BCOL;
  markerMsgs.markers[6].lifetime = ros::Duration();

  // initialize second Marker message
  markerMsgs.markers[7].header.frame_id = "finger3_middle";
  markerMsgs.markers[7].ns = "my_namespace";
  markerMsgs.markers[7].id = 7;
  markerMsgs.markers[7].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[7].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[7].pose.position.x = XPOS-0.064;
  markerMsgs.markers[7].pose.position.y = YPOS-0.008;
  markerMsgs.markers[7].pose.position.z = ZPOS+0.045;
  markerMsgs.markers[7].pose.orientation.x = -0.1;
  markerMsgs.markers[7].pose.orientation.y = 0;
  markerMsgs.markers[7].pose.orientation.z = 0;
  markerMsgs.markers[7].pose.orientation.w = 0.994987437;
  markerMsgs.markers[7].scale.z = SCALE;
  markerMsgs.markers[7].scale.x = SCALE;
  markerMsgs.markers[7].scale.y = SCALE;
  markerMsgs.markers[7].color.a = ACOL;
  markerMsgs.markers[7].color.r = RCOL;
  markerMsgs.markers[7].color.g = GCOL;
  markerMsgs.markers[7].color.b = BCOL;
  markerMsgs.markers[7].lifetime = ros::Duration();

  // initialize third Marker message
  markerMsgs.markers[8].header.frame_id = "finger3_tip";
  markerMsgs.markers[8].ns = "my_namespace";
  markerMsgs.markers[8].id = 8;
  markerMsgs.markers[8].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[8].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[8].pose.position.x = XPOS-0.065;
  markerMsgs.markers[8].pose.position.y = YPOS-0.009;
  markerMsgs.markers[8].pose.position.z = ZPOS+0.015;
  markerMsgs.markers[8].pose.orientation.x = -0.2;
  markerMsgs.markers[8].pose.orientation.y = 0;
  markerMsgs.markers[8].pose.orientation.z = 0;
  markerMsgs.markers[8].pose.orientation.w = 0.979795897;
  markerMsgs.markers[8].scale.z = SCALE;
  markerMsgs.markers[8].scale.x = SCALE;
  markerMsgs.markers[8].scale.y = SCALE;
  markerMsgs.markers[8].color.a = ACOL;
  markerMsgs.markers[8].color.r = RCOL;
  markerMsgs.markers[8].color.g = GCOL;
  markerMsgs.markers[8].color.b = BCOL;
  markerMsgs.markers[8].lifetime = ros::Duration();

  // initialize sensor markers on the fourth finger
  // initialize first Marker message
  markerMsgs.markers[9].header.frame_id = "finger4_middle";
  markerMsgs.markers[9].ns = "my_namespace";
  markerMsgs.markers[9].id = 9;
  markerMsgs.markers[9].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[9].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[9].pose.position.x = XPOS-0.082;
  markerMsgs.markers[9].pose.position.y = YPOS-0.018;
  markerMsgs.markers[9].pose.position.z = ZPOS+0.021;
  markerMsgs.markers[9].pose.orientation.x = 0;
  markerMsgs.markers[9].pose.orientation.y = 0;
  markerMsgs.markers[9].pose.orientation.z = 0;
  markerMsgs.markers[9].pose.orientation.w = 1;
  markerMsgs.markers[9].scale.z = SCALE;
  markerMsgs.markers[9].scale.x = SCALE;
  markerMsgs.markers[9].scale.y = SCALE;
  markerMsgs.markers[9].color.a = ACOL;
  markerMsgs.markers[9].color.r = RCOL;
  markerMsgs.markers[9].color.g = GCOL;
  markerMsgs.markers[9].color.b = BCOL;
  markerMsgs.markers[9].lifetime = ros::Duration();

  // initialize second Marker message
  markerMsgs.markers[10].header.frame_id = "finger4_middle";
  markerMsgs.markers[10].ns = "my_namespace";
  markerMsgs.markers[10].id = 10;
  markerMsgs.markers[10].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[10].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[10].pose.position.x = XPOS-0.084;
  markerMsgs.markers[10].pose.position.y = YPOS-0.019;
  markerMsgs.markers[10].pose.position.z = ZPOS+0.036;
  markerMsgs.markers[10].pose.orientation.x = 0;
  markerMsgs.markers[10].pose.orientation.y = 0;
  markerMsgs.markers[10].pose.orientation.z = 0;
  markerMsgs.markers[10].pose.orientation.w = 1;
  markerMsgs.markers[10].scale.z = SCALE;
  markerMsgs.markers[10].scale.x = SCALE;
  markerMsgs.markers[10].scale.y = SCALE;
  markerMsgs.markers[10].color.a = ACOL;
  markerMsgs.markers[10].color.r = RCOL;
  markerMsgs.markers[10].color.g = GCOL;
  markerMsgs.markers[10].color.b = BCOL;
  markerMsgs.markers[10].lifetime = ros::Duration();

  // initialize third Marker message
  markerMsgs.markers[11].header.frame_id = "finger4_tip";
  markerMsgs.markers[11].ns = "my_namespace";
  markerMsgs.markers[11].id = 11;
  markerMsgs.markers[11].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[11].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[11].pose.position.x = XPOS-0.088;
  markerMsgs.markers[11].pose.position.y = YPOS-0.018;
  markerMsgs.markers[11].pose.position.z = ZPOS+0.02;
  markerMsgs.markers[11].pose.orientation.x = 0;
  markerMsgs.markers[11].pose.orientation.y = 0;
  markerMsgs.markers[11].pose.orientation.z = 0;
  markerMsgs.markers[11].pose.orientation.w = 1;  
  markerMsgs.markers[11].scale.z = SCALE;
  markerMsgs.markers[11].scale.x = SCALE;
  markerMsgs.markers[11].scale.y = SCALE;
  markerMsgs.markers[11].color.a = ACOL;
  markerMsgs.markers[11].color.r = RCOL;
  markerMsgs.markers[11].color.g = GCOL;
  markerMsgs.markers[11].color.b = BCOL;
  markerMsgs.markers[11].lifetime = ros::Duration();

  // initialize sensor markers on the thumb
  // initialize first Marker message
  markerMsgs.markers[12].header.frame_id = "thumb_base";
  markerMsgs.markers[12].ns = "my_namespace";
  markerMsgs.markers[12].id = 12;
  markerMsgs.markers[12].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[12].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[12].pose.position.x = XPOS+0.0055;
  markerMsgs.markers[12].pose.position.y = YPOS-0.01;
  markerMsgs.markers[12].pose.position.z = ZPOS+0.019;
  markerMsgs.markers[12].pose.orientation.x = 0;
  markerMsgs.markers[12].pose.orientation.y = 0;
  markerMsgs.markers[12].pose.orientation.z = 0;
  markerMsgs.markers[12].pose.orientation.w = 1;
  markerMsgs.markers[12].scale.z = SCALE;
  markerMsgs.markers[12].scale.x = SCALE;
  markerMsgs.markers[12].scale.y = SCALE;
  markerMsgs.markers[12].color.a = ACOL;
  markerMsgs.markers[12].color.r = RCOL;
  markerMsgs.markers[12].color.g = GCOL;
  markerMsgs.markers[12].color.b = BCOL;
  markerMsgs.markers[12].lifetime = ros::Duration();

  // initialize second Marker message
  markerMsgs.markers[13].header.frame_id = "thumb_middle";
  markerMsgs.markers[13].ns = "my_namespace";
  markerMsgs.markers[13].id = 13;
  markerMsgs.markers[13].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[13].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[13].pose.position.x = XPOS-0.005;
  markerMsgs.markers[13].pose.position.y = YPOS-0.005;
  markerMsgs.markers[13].pose.position.z = ZPOS+0.03;
  markerMsgs.markers[13].pose.orientation.x = 0;
  markerMsgs.markers[13].pose.orientation.y = 0;
  markerMsgs.markers[13].pose.orientation.z = 0;
  markerMsgs.markers[13].pose.orientation.w = 1;  
  markerMsgs.markers[13].scale.z = SCALE;
  markerMsgs.markers[13].scale.x = SCALE;
  markerMsgs.markers[13].scale.y = SCALE;
  markerMsgs.markers[13].color.a = ACOL;
  markerMsgs.markers[13].color.r = RCOL;
  markerMsgs.markers[13].color.g = GCOL;
  markerMsgs.markers[13].color.b = BCOL;
  markerMsgs.markers[13].lifetime = ros::Duration();

  // initialize third Marker message
  markerMsgs.markers[14].header.frame_id = "thumb_tip";
  markerMsgs.markers[14].ns = "my_namespace";
  markerMsgs.markers[14].id = 14;
  markerMsgs.markers[14].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[14].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[14].pose.position.x = XPOS-0.015;
  markerMsgs.markers[14].pose.position.y = YPOS+0.004;
  markerMsgs.markers[14].pose.position.z = ZPOS+0.02;
  markerMsgs.markers[14].pose.orientation.x = 0;
  markerMsgs.markers[14].pose.orientation.y = 0;
  markerMsgs.markers[14].pose.orientation.z = 0;
  markerMsgs.markers[14].pose.orientation.w = 1;  
  markerMsgs.markers[14].scale.z = SCALE;
  markerMsgs.markers[14].scale.x = SCALE;
  markerMsgs.markers[14].scale.y = SCALE;
  markerMsgs.markers[14].color.a = ACOL;
  markerMsgs.markers[14].color.r = RCOL;
  markerMsgs.markers[14].color.g = GCOL;
  markerMsgs.markers[14].color.b = BCOL;
  markerMsgs.markers[14].lifetime = ros::Duration();

  // initialize sensor markers on the palm
  // initialize first row first Marker message
  markerMsgs.markers[15].header.frame_id = "hand_base";
  markerMsgs.markers[15].ns = "my_namespace";
  markerMsgs.markers[15].id = 15;
  markerMsgs.markers[15].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[15].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[15].pose.position.x = XPOS+0.008;
  markerMsgs.markers[15].pose.position.y = YPOS-0.015;
  markerMsgs.markers[15].pose.position.z = ZPOS+0.075;
  markerMsgs.markers[15].pose.orientation.x = 0;
  markerMsgs.markers[15].pose.orientation.y = 0;
  markerMsgs.markers[15].pose.orientation.z = 0;
  markerMsgs.markers[15].pose.orientation.w = 1;
  markerMsgs.markers[15].scale.z = SCALE;
  markerMsgs.markers[15].scale.x = SCALE;
  markerMsgs.markers[15].scale.y = SCALE;
  markerMsgs.markers[15].color.a = ACOL;
  markerMsgs.markers[15].color.r = RCOL;
  markerMsgs.markers[15].color.g = GCOL;
  markerMsgs.markers[15].color.b = BCOL;
  markerMsgs.markers[15].lifetime = ros::Duration();

  // initialize first row second Marker message
  markerMsgs.markers[16].header.frame_id = "hand_base";
  markerMsgs.markers[16].ns = "my_namespace";
  markerMsgs.markers[16].id = 16;
  markerMsgs.markers[16].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[16].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[16].pose.position.x = XPOS-0.008;
  markerMsgs.markers[16].pose.position.y = YPOS-0.015;
  markerMsgs.markers[16].pose.position.z = ZPOS+0.075;
  markerMsgs.markers[16].pose.orientation.x = 0;
  markerMsgs.markers[16].pose.orientation.y = 0;
  markerMsgs.markers[16].pose.orientation.z = 0;
  markerMsgs.markers[16].pose.orientation.w = 1;
  markerMsgs.markers[16].scale.z = SCALE;
  markerMsgs.markers[16].scale.x = SCALE;
  markerMsgs.markers[16].scale.y = SCALE;
  markerMsgs.markers[16].color.a = ACOL;
  markerMsgs.markers[16].color.r = RCOL;
  markerMsgs.markers[16].color.g = GCOL;
  markerMsgs.markers[16].color.b = BCOL;
  markerMsgs.markers[16].lifetime = ros::Duration();

  // initialize first row third Marker message
  markerMsgs.markers[17].header.frame_id = "hand_base";
  markerMsgs.markers[17].ns = "my_namespace";
  markerMsgs.markers[17].id = 17;
  markerMsgs.markers[17].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[17].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[17].pose.position.x = XPOS-0.024;
  markerMsgs.markers[17].pose.position.y = YPOS-0.015;
  markerMsgs.markers[17].pose.position.z = ZPOS+0.075;
  markerMsgs.markers[17].pose.orientation.x = 0;
  markerMsgs.markers[17].pose.orientation.y = 0;
  markerMsgs.markers[17].pose.orientation.z = 0;
  markerMsgs.markers[17].pose.orientation.w = 1;
  markerMsgs.markers[17].scale.z = SCALE;
  markerMsgs.markers[17].scale.x = SCALE;
  markerMsgs.markers[17].scale.y = SCALE;
  markerMsgs.markers[17].color.a = ACOL;
  markerMsgs.markers[17].color.r = RCOL;
  markerMsgs.markers[17].color.g = GCOL;
  markerMsgs.markers[17].color.b = BCOL;
  markerMsgs.markers[17].lifetime = ros::Duration();

  // initialize second row first Marker message
  markerMsgs.markers[18].header.frame_id = "hand_base";
  markerMsgs.markers[18].ns = "my_namespace";
  markerMsgs.markers[18].id = 18;
  markerMsgs.markers[18].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[18].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[18].pose.position.x = XPOS+0.008;
  markerMsgs.markers[18].pose.position.y = YPOS-0.01;
  markerMsgs.markers[18].pose.position.z = ZPOS+0.06;
  markerMsgs.markers[18].pose.orientation.x = 0;
  markerMsgs.markers[18].pose.orientation.y = 0;
  markerMsgs.markers[18].pose.orientation.z = 0;
  markerMsgs.markers[18].pose.orientation.w = 1;  
  markerMsgs.markers[18].scale.z = SCALE;
  markerMsgs.markers[18].scale.x = SCALE;
  markerMsgs.markers[18].scale.y = SCALE;
  markerMsgs.markers[18].color.a = ACOL;
  markerMsgs.markers[18].color.r = RCOL;
  markerMsgs.markers[18].color.g = GCOL;
  markerMsgs.markers[18].color.b = BCOL;
  markerMsgs.markers[18].lifetime = ros::Duration();

  // initialize second row second Marker message
  markerMsgs.markers[19].header.frame_id = "hand_base";
  markerMsgs.markers[19].ns = "my_namespace";
  markerMsgs.markers[19].id = 19;
  markerMsgs.markers[19].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[19].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[19].pose.position.x = XPOS-0.008;
  markerMsgs.markers[19].pose.position.y = YPOS-0.01;
  markerMsgs.markers[19].pose.position.z = ZPOS+0.06;
  markerMsgs.markers[19].pose.orientation.x = 0;
  markerMsgs.markers[19].pose.orientation.y = 0;
  markerMsgs.markers[19].pose.orientation.z = 0;
  markerMsgs.markers[19].pose.orientation.w = 1;  
  markerMsgs.markers[19].scale.z = SCALE;
  markerMsgs.markers[19].scale.x = SCALE;
  markerMsgs.markers[19].scale.y = SCALE;
  markerMsgs.markers[19].color.a = ACOL;
  markerMsgs.markers[19].color.r = RCOL;
  markerMsgs.markers[19].color.g = GCOL;
  markerMsgs.markers[19].color.b = BCOL;
  markerMsgs.markers[19].lifetime = ros::Duration();

  // initialize second row third Marker message
  markerMsgs.markers[20].header.frame_id = "hand_base";
  markerMsgs.markers[20].ns = "my_namespace";
  markerMsgs.markers[20].id = 20;
  markerMsgs.markers[20].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[20].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[20].pose.position.x = XPOS-0.024;
  markerMsgs.markers[20].pose.position.y = YPOS-0.01;
  markerMsgs.markers[20].pose.position.z = ZPOS+0.06;
  markerMsgs.markers[20].pose.orientation.x = 0;
  markerMsgs.markers[20].pose.orientation.y = 0;
  markerMsgs.markers[20].pose.orientation.z = 0;
  markerMsgs.markers[20].pose.orientation.w = 1;  
  markerMsgs.markers[20].scale.z = SCALE;
  markerMsgs.markers[20].scale.x = SCALE;
  markerMsgs.markers[20].scale.y = SCALE;
  markerMsgs.markers[20].color.a = ACOL;
  markerMsgs.markers[20].color.r = RCOL;
  markerMsgs.markers[20].color.g = GCOL;
  markerMsgs.markers[20].color.b = BCOL;
  markerMsgs.markers[20].lifetime = ros::Duration();

  // initialize third row first Marker message
  markerMsgs.markers[21].header.frame_id = "hand_base";
  markerMsgs.markers[21].ns = "my_namespace";
  markerMsgs.markers[21].id = 21;
  markerMsgs.markers[21].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[21].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[21].pose.position.x = XPOS+0.008;
  markerMsgs.markers[21].pose.position.y = YPOS-0.0075;
  markerMsgs.markers[21].pose.position.z = ZPOS+0.045;
  markerMsgs.markers[21].pose.orientation.x = 0;
  markerMsgs.markers[21].pose.orientation.y = 0;
  markerMsgs.markers[21].pose.orientation.z = 0;
  markerMsgs.markers[21].pose.orientation.w = 1;
  markerMsgs.markers[21].scale.z = SCALE;
  markerMsgs.markers[21].scale.x = SCALE;
  markerMsgs.markers[21].scale.y = SCALE;
  markerMsgs.markers[21].color.a = ACOL;
  markerMsgs.markers[21].color.r = RCOL;
  markerMsgs.markers[21].color.g = GCOL;
  markerMsgs.markers[21].color.b = BCOL;
  markerMsgs.markers[21].lifetime = ros::Duration();

  // initialize third row second Marker message
  markerMsgs.markers[22].header.frame_id = "hand_base";
  markerMsgs.markers[22].ns = "my_namespace";
  markerMsgs.markers[22].id = 22;
  markerMsgs.markers[22].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[22].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[22].pose.position.x = XPOS-0.008;
  markerMsgs.markers[22].pose.position.y = YPOS-0.0075;
  markerMsgs.markers[22].pose.position.z = ZPOS+0.045;
  markerMsgs.markers[22].pose.orientation.x = 0;
  markerMsgs.markers[22].pose.orientation.y = 0;
  markerMsgs.markers[22].pose.orientation.z = 0;
  markerMsgs.markers[22].pose.orientation.w = 1;
  markerMsgs.markers[22].scale.z = SCALE;
  markerMsgs.markers[22].scale.x = SCALE;
  markerMsgs.markers[22].scale.y = SCALE;
  markerMsgs.markers[22].color.a = ACOL;
  markerMsgs.markers[22].color.r = RCOL;
  markerMsgs.markers[22].color.g = GCOL;
  markerMsgs.markers[22].color.b = BCOL;
  markerMsgs.markers[22].lifetime = ros::Duration();

  // initialize third row third Marker message
  markerMsgs.markers[23].header.frame_id = "hand_base";
  markerMsgs.markers[23].ns = "my_namespace";
  markerMsgs.markers[23].id = 23;
  markerMsgs.markers[23].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[23].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[23].pose.position.x = XPOS-0.024;
  markerMsgs.markers[23].pose.position.y = YPOS-0.0075;
  markerMsgs.markers[23].pose.position.z = ZPOS+0.045;
  markerMsgs.markers[23].pose.orientation.x = 0;
  markerMsgs.markers[23].pose.orientation.y = 0;
  markerMsgs.markers[23].pose.orientation.z = 0;
  markerMsgs.markers[23].pose.orientation.w = 1;
  markerMsgs.markers[23].scale.z = SCALE;
  markerMsgs.markers[23].scale.x = SCALE;
  markerMsgs.markers[23].scale.y = SCALE;
  markerMsgs.markers[23].color.a = ACOL;
  markerMsgs.markers[23].color.r = RCOL;
  markerMsgs.markers[23].color.g = GCOL;
  markerMsgs.markers[23].color.b = BCOL;
  markerMsgs.markers[23].lifetime = ros::Duration();

  // initialize fourth row first Marker message
  markerMsgs.markers[24].header.frame_id = "hand_base";
  markerMsgs.markers[24].ns = "my_namespace";
  markerMsgs.markers[24].id = 24;
  markerMsgs.markers[24].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[24].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[24].pose.position.x = XPOS+0.008;
  markerMsgs.markers[24].pose.position.y = YPOS-0.005;
  markerMsgs.markers[24].pose.position.z = ZPOS+0.03;
  markerMsgs.markers[24].pose.orientation.x = 0;
  markerMsgs.markers[24].pose.orientation.y = 0;
  markerMsgs.markers[24].pose.orientation.z = 0;
  markerMsgs.markers[24].pose.orientation.w = 1;  
  markerMsgs.markers[24].scale.z = SCALE;
  markerMsgs.markers[24].scale.x = SCALE;
  markerMsgs.markers[24].scale.y = SCALE;
  markerMsgs.markers[24].color.a = ACOL;
  markerMsgs.markers[24].color.r = RCOL;
  markerMsgs.markers[24].color.g = GCOL;
  markerMsgs.markers[24].color.b = BCOL;
  markerMsgs.markers[24].lifetime = ros::Duration();

  // initialize fourth row second Marker message
  markerMsgs.markers[25].header.frame_id = "hand_base";
  markerMsgs.markers[25].ns = "my_namespace";
  markerMsgs.markers[25].id = 25;
  markerMsgs.markers[25].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[25].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[25].pose.position.x = XPOS-0.008;
  markerMsgs.markers[25].pose.position.y = YPOS-0.005;
  markerMsgs.markers[25].pose.position.z = ZPOS+0.03;
  markerMsgs.markers[25].pose.orientation.x = 0;
  markerMsgs.markers[25].pose.orientation.y = 0;
  markerMsgs.markers[25].pose.orientation.z = 0;
  markerMsgs.markers[25].pose.orientation.w = 1;  
  markerMsgs.markers[25].scale.z = SCALE;
  markerMsgs.markers[25].scale.x = SCALE;
  markerMsgs.markers[25].scale.y = SCALE;
  markerMsgs.markers[25].color.a = ACOL;
  markerMsgs.markers[25].color.r = RCOL;
  markerMsgs.markers[25].color.g = GCOL;
  markerMsgs.markers[25].color.b = BCOL;
  markerMsgs.markers[25].lifetime = ros::Duration();

  // initialize fourth row third Marker message
  markerMsgs.markers[26].header.frame_id = "hand_base";
  markerMsgs.markers[26].ns = "my_namespace";
  markerMsgs.markers[26].id = 26;
  markerMsgs.markers[26].type = visualization_msgs::Marker::CUBE;
  markerMsgs.markers[26].action = visualization_msgs::Marker::ADD;
  markerMsgs.markers[26].pose.position.x = XPOS-0.024;
  markerMsgs.markers[26].pose.position.y = YPOS-0.005;
  markerMsgs.markers[26].pose.position.z = ZPOS+0.03;
  markerMsgs.markers[26].pose.orientation.x = 0;
  markerMsgs.markers[26].pose.orientation.y = 0;
  markerMsgs.markers[26].pose.orientation.z = 0;
  markerMsgs.markers[26].pose.orientation.w = 1;  
  markerMsgs.markers[26].scale.z = SCALE;
  markerMsgs.markers[26].scale.x = SCALE;
  markerMsgs.markers[26].scale.y = SCALE;
  markerMsgs.markers[26].color.a = ACOL;
  markerMsgs.markers[26].color.r = RCOL;
  markerMsgs.markers[26].color.g = GCOL;
  markerMsgs.markers[26].color.b = BCOL;
  markerMsgs.markers[26].lifetime = ros::Duration();

  // create the subscriber to sensors
  ros::Subscriber sub = n.subscribe("hand/sensors", 10, sensorsCallback);

  // spin the callback
  ros::spin();
  
  return 0;
}

void sensorsCallback(const sensor_msgs::JointState::ConstPtr& msg){

  double count1a = msg->position.at(0), 
    count1b = msg->position.at(1), 
    count2a = msg->position.at(2), 
    count2b = msg->position.at(3), 
    count3a = msg->position.at(4), 
    count3b = msg->position.at(5), 
    count4a = msg->position.at(6), 
    count4b = msg->position.at(7), 
    count0a = msg->position.at(8), 
    count0c = msg->position.at(9);


  // adjust the angle of the fingers in the JointState message.
  // order is {"finger1a", "finger1b", "finger2a", "finger2b", "finger3a", "finger3b", "finger4a", "finger4b", "thumba", "thumbc"}
  jointMsg.header.stamp = ros::Time();
  jointMsg.position = {count1a, count1b, count2a, count2b, count3a, count3b, count4a, count4b, count0a, count0c};

  // adjust the values of the force sensors in the Markers. WORK IN PROGRESS; need to add color variation

  markerMsgs.markers[0].header.stamp = ros::Time();
  markerMsgs.markers[1].header.stamp = ros::Time();    
  markerMsgs.markers[2].header.stamp = ros::Time();   
  markerMsgs.markers[3].header.stamp = ros::Time();
  markerMsgs.markers[4].header.stamp = ros::Time();
  markerMsgs.markers[5].header.stamp = ros::Time();
  markerMsgs.markers[6].header.stamp = ros::Time();
  markerMsgs.markers[7].header.stamp = ros::Time();
  markerMsgs.markers[8].header.stamp = ros::Time();
  markerMsgs.markers[9].header.stamp = ros::Time();
  markerMsgs.markers[10].header.stamp = ros::Time();
  markerMsgs.markers[11].header.stamp = ros::Time();
  markerMsgs.markers[12].header.stamp = ros::Time();
  markerMsgs.markers[13].header.stamp = ros::Time();
  markerMsgs.markers[14].header.stamp = ros::Time();
  markerMsgs.markers[15].header.stamp = ros::Time();
  markerMsgs.markers[16].header.stamp = ros::Time();
  markerMsgs.markers[17].header.stamp = ros::Time();
  markerMsgs.markers[18].header.stamp = ros::Time();
  markerMsgs.markers[19].header.stamp = ros::Time();
  markerMsgs.markers[20].header.stamp = ros::Time();
  markerMsgs.markers[21].header.stamp = ros::Time();
  markerMsgs.markers[22].header.stamp = ros::Time();
  markerMsgs.markers[23].header.stamp = ros::Time();
  markerMsgs.markers[24].header.stamp = ros::Time();
  markerMsgs.markers[25].header.stamp = ros::Time();
  markerMsgs.markers[26].header.stamp = ros::Time();

  // publish both messages
  (*pubPtr1).publish(jointMsg);
  (*pubPtr2).publish(markerMsgs);
}