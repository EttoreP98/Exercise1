#include <ros/ros.h>
#include <std_msgs/String.h>
#include <trajectory_msgs/JointTrajectory.h>


void chatterCallback(const trajectory_msgs::JointTrajectory& msg){

    for(int i=0;i<6;i++){
        ROS_INFO_STREAM(" Giunto: "<<msg.joint_names[i]);
        ROS_INFO_STREAM(" Punto: "<<msg.points[i]);
        
    }
}

int main(int argc, char **argv)
{
ros::init(argc, argv, "listener");
ros::NodeHandle nodeHandle;
ros::Subscriber subscriber =
nodeHandle.subscribe("motor_chatter",10,chatterCallback);
ros::spin();
return 0;
}