#include <ros/ros.h>
#include <iostream>
#include "keyboard.h"
#include "std_msgs/Float64.h"

using namespace std;



/*///////////////////////////////////////////////////
class myfunction
{
public:
double a;
double b;

myfunction(double c,double d)
{
a = c;
b = d;
}

double sum() 
{
return (a+b);
}

};
///////////////////////////////////////////////////*/

class SubscribeAndPublish
{
public:
SubscribeAndPublish()
{

joint_pub = n.advertise<std_msgs::Float64>("/rrbot/joint2_position_controller/command", 10);

des_velocity_down = n.subscribe<keyboard::Key>("/keyboard/keydown", 10, &SubscribeAndPublish::KeyCallbackdown, this);

des_velocity_up = n.subscribe<keyboard::Key>("/keyboard/keyup", 10, &SubscribeAndPublish::KeyCallbackup, this);



}

void KeyCallbackdown(const keyboard::Key::ConstPtr& msg)
{

keyboard::Key k;


k = *msg;

switch(k.code){
case(273):
joint_position.data += joint_vel.data*0.01;
break;
case(274):
joint_position.data += joint_vel.data*(-0.01);
break;
case(270):
joint_vel.data = 0.01+joint_vel.data;
break;
case(269):
joint_vel.data = -0.01+joint_vel.data;
break;
}

joint_pub.publish(joint_position);
ROS_INFO_STREAM(joint_position.data*57);

return;
}


void KeyCallbackup(const keyboard::Key::ConstPtr& msg)
{

joint_position.data += 0;

joint_pub.publish(joint_position);

return;
}

private:
ros::NodeHandle n;
ros::Publisher joint_pub;
ros::Subscriber des_velocity_up;
ros::Subscriber des_velocity_down;
std_msgs::Float64 joint_position;

std_msgs::Float64 joint_vel;

};

//////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{

ros::init(argc,argv,"keyboard_subscriber_node");
ros::NodeHandle n;
ros::Rate r(10);

SubscribeAndPublish SAPObject;

r.sleep();
ros::spin();

return 0;
}
