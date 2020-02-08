#include <ros/ros.h>
#include <ros_myo/EmgArray.h>
#include <intera_core_msgs/JointCommand.h>


intera_core_msgs::JointCommand jc_msg;

void callback(const ros_myo::EmgArrayConstPtr& msg)
{
  jc_msg.names.resize(1);
  jc_msg.position.resize(1);
  jc_msg.mode = 1;
  jc_msg.names.at(0) = "right_j0";

  if (msg->data.at(1) > 200 && msg->data.at(2) > 200 && msg->data.at(3) > 200)
  {
    jc_msg.position.at(0) = 1.5;
    std::cout << "UP" << std::endl;
  }
  else
  {
    jc_msg.position.at(0) = 1.0;
    std::cout << "HOME" << std::endl;
  }
}


int main(int argc, char **argv){

    ros::init(argc, argv, "myo_control");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/myo_raw/myo_emg",1,callback);
    ros::Publisher pub = nh.advertise<intera_core_msgs::JointCommand>("/robot/limb/right/joint_command",1);
    
    while (ros::ok())
    {
        pub.publish(jc_msg);
        ros::spinOnce();
    }
    
}