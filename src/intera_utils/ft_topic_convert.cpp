#include <ros/ros.h>
#include <geometry_msgs/WrenchStamped.h>
#include <intera_core_msgs/EndpointState.h>



geometry_msgs::WrenchStamped ws_msg;

void callback(const intera_core_msgs::EndpointStateConstPtr& msg)
{

  ws_msg.header = msg->header;
  ws_msg.wrench.force.x = - msg->wrench.force.x;
  ws_msg.wrench.force.y = - msg->wrench.force.y;
  ws_msg.wrench.force.z = - msg->wrench.force.z;
  ws_msg.wrench.torque.x = - msg->wrench.torque.x;
  ws_msg.wrench.torque.y = - msg->wrench.torque.y;
  ws_msg.wrench.torque.z = - msg->wrench.torque.z;

}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "ft_topic_converter");
  ros::NodeHandle nh;


  ros::Subscriber sub = nh.subscribe("/robot/limb/right/endpoint_state", 1, callback);
  ros::Publisher pub = nh.advertise<geometry_msgs::WrenchStamped>("/robot/limb/right/wrench",1);


  ROS_INFO("Ready to convert topics");
  while (ros::ok())
  {
      pub.publish(ws_msg);
      ros::spinOnce();
  }
  
  return 0;
}