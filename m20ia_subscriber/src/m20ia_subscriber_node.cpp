#include <ros/ros.h>
#include <tf/tf.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <string>


void print_matrix(geometry_msgs::TransformStamped transformStamped){
    tf::Quaternion q;
    q.setW(transformStamped.transform.rotation.w);
    q.setX(transformStamped.transform.rotation.x);
    q.setY(transformStamped.transform.rotation.y);
    q.setZ(transformStamped.transform.rotation.z);

//Quaternioni -> Matrice di rotazione
    tf::Matrix3x3 m(q);
    
//Matrice di Rotazione -> RPY
  double roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw);

//Quaternioni -> Asse angolo
  tf::Vector3 axis = q.getAxis();

    ROS_INFO_STREAM(
     transformStamped  
     <<"\nMatrice di Rotazione :\n"
     << "[" << m.getRow(0)[0] <<"\t" << m.getRow(0)[1] <<"\t" <<m.getRow(0)[2] << "]" <<"\n"
     << "[" << m.getRow(1)[0] <<"\t" << m.getRow(1)[1] <<"\t" <<m.getRow(1)[2] << "]" <<"\n"
     << "[" << m.getRow(2)[0] <<"\t" << m.getRow(2)[1] <<"\t" <<m.getRow(2)[2] << "]" <<"\n" 
     <<"\n"
     << "RPY:\n" 
     <<"[" << roll <<"\t" << pitch <<"\t" <<yaw << "]" <<"\n"
     <<"\n"
     <<"Asse-Angolo:\n"
     <<"Asse: [" << axis[0] << "\t" << axis[1] <<"\t" <<axis[2] << "]" << "    Angolo : [" << q.getAngle() << "]" 
     << "\n"
     << "-----------------------------------------------------------------------------------------------------"
     << "\n");

}


int main(int argc, char** argv) {
    ros::init(argc, argv, "tf2_listener");
    tf2_ros::Buffer tfBuffer[6];
    tf2_ros::TransformListener tfListener1(tfBuffer[0]),tfListener2(tfBuffer[1]),tfListener3(tfBuffer[2]),tfListener4(tfBuffer[3]),tfListener5(tfBuffer[4]),
    tfListener6(tfBuffer[5]);



    ros::Rate rate(10.0);
    
    while(ros::ok()) {
        geometry_msgs::TransformStamped transformStamped;
        try{
            for (int i = 1; i < 6; i++)
            {
                transformStamped = tfBuffer[i-1].lookupTransform("base_link","link"+std::to_string(i), ros::Time(0));
                print_matrix(transformStamped);
            }
        }
        catch (tf2::TransformException &exception) {
            ROS_WARN("%s", exception.what());
            ros::Duration(1.0).sleep();
            continue;
        }
        rate.sleep();
    }
    return 0;
};