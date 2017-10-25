#include <ros/ros.h>
#include <iostream>
#include "keyboard.h"
#include <geometry_msgs/Twist.h>

using namespace std;

///////////////////////////////////////////////////*/
keyboard::Key k;
geometry_msgs::Twist desired_motion;

class SubscribeAndPublish
{
public:
SubscribeAndPublish()
{

turtle_vel = n.advertise<geometry_msgs::Twist>("/cmd_vel",1000);

des_velocity_down = n.subscribe<keyboard::Key>("/keyboard/keydown", 1000, &SubscribeAndPublish::KeyCallbackdown, this);

des_velocity_up = n.subscribe<keyboard::Key>("/keyboard/keyup", 1000, &SubscribeAndPublish::KeyCallbackup, this);



}

void KeyCallbackdown(const keyboard::Key::ConstPtr& msg)
{

k = *msg;

switch(k.code){
case(263): //7
desired_motion.linear.x += 0.01;
break;
case(260): //4
desired_motion.linear.x = 0;
break;
case(257): //1
desired_motion.linear.x += -0.01;
break;

case(264): //8
desired_motion.linear.y += 0.01;
break;
case(261): //5
desired_motion.linear.y = 0;
break;
case(258): //2
desired_motion.linear.y += -0.01;
break;

case(265): //9
desired_motion.linear.z += 0.01;
break;
case(262): //6
desired_motion.linear.z = 0;
break;
case(259): //3
desired_motion.linear.z += -0.01;
break;

//Angular speed
case(113): //Q
desired_motion.angular.x += 0.01;
break;
case(97): //A
desired_motion.angular.x = 0;
break;
case(122): //Z
desired_motion.angular.x += -0.01;
break;

case(119): //W
desired_motion.angular.y += 0.01;
break;
case(115): //S
desired_motion.angular.y = 0;
break;
case(120): //X
desired_motion.angular.y += -0.01;
break;

case(101): //E
desired_motion.angular.z += 0.01;
break;
case(100): //D
desired_motion.angular.z = 0;
break;
case(99): //C
desired_motion.angular.z += -0.01;
break;


}

turtle_vel.publish(desired_motion);

return;
}


void KeyCallbackup(const keyboard::Key::ConstPtr& msg)
{
// If not pressed, keep sending old message
turtle_vel.publish(desired_motion);
return;
}


private:



ros::NodeHandle n;
ros::Publisher turtle_vel;
ros::Subscriber des_velocity_up;
ros::Subscriber des_velocity_down;
};

//////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
ros::init(argc,argv,"keyboard_subscriber_twist_node");
ros::NodeHandle n;
ros::Rate r(10);

SubscribeAndPublish SAPObject;


ros::spin();
return 0;
}
