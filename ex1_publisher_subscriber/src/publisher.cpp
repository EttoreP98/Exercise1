#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>
#include <std_msgs/String.h>
#include <time.h> 
#include <string.h>

using namespace std;  

int main(int argc,char ** argv){
    ros::init(argc,argv,"talker");
    ros::NodeHandle nh;
    ros::Publisher chatterPublisher =
    nh.advertise<trajectory_msgs::JointTrajectory> ("motor_chatter",1);
    ros::Rate loopRate(1);

    srand(time(NULL));

    while (ros::ok())
    {
        trajectory_msgs::JointTrajectory jointRobot;

        for (int i = 0; i < 6; i++){
            jointRobot.joint_names.push_back("joint_"+to_string(i));
        }        
        
        trajectory_msgs::JointTrajectoryPoint tjp1,tjp2,tjp3,tjp4,tjp5,tjp6;

        jointRobot.points.push_back(tjp1);
        jointRobot.points.push_back(tjp2);
        jointRobot.points.push_back(tjp3);
        jointRobot.points.push_back(tjp4);
        jointRobot.points.push_back(tjp5);
        jointRobot.points.push_back(tjp6);

        for (int i = 0; i < 6; i++){
            jointRobot.points[i].positions.resize(3);
            for (int j = 0; j < 3; j++){
                jointRobot.points[i].positions[j]=rand();
            }
        }
        
        for (int i = 0; i < 6; i++){
            ROS_INFO_STREAM(" Giunto: "<<jointRobot.joint_names[i]);
            ROS_INFO_STREAM(" Punto: "<<jointRobot.points[i]);
        }

        chatterPublisher.publish(jointRobot);
        
        
        ros::spinOnce();
        loopRate.sleep();
    }   
    return 0;    
}