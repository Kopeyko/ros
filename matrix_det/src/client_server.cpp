#include "ros/ros.h"
#include "matrix_det/count_matrix_det.h"
#include "std_msgs/Float32.h"

ros::ServiceServer service;
ros::Publisher pub;
ros::Subscriber sub;


bool count_determinant(matrix_det::count_matrix_det::Request &req, matrix_det::count_matrix_det::Response &res)
{
    float first_part = (req.num_1*req.num_5*req.num_9) + (req.num_2*req.num_6*req.num_7) + (req.num_3*req.num_4*req.num_8);
    float second_part = -(req.num_3*req.num_5*req.num_7) - (req.num_1*req.num_6*req.num_8) - (req.num_2*req.num_4*req.num_9);
    res.determinant = first_part + second_part;
    ROS_INFO("request: %d %d %d  %d %d %d  %d %d %d", req.num_1,  req.num_2,  req.num_3, req.num_4, req.num_5, req.num_6, req.num_7, req.num_8, req.num_9);
    ROS_INFO("sending back response: %f", res.determinant);
    
    std_msgs::Float32 det;
    det.data = res.determinant;
    pub.publish(det);
    return true;
}

void recieve(const std_msgs::Float32& det_from_topic)
{
    if (((int)det_from_topic.data%2) == 0){
        ROS_INFO("even");
    } else
    {
        ROS_INFO("odd");
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "matrix_det");
    ros::NodeHandle n;
    service = n.advertiseService("matrix_det", count_determinant);
    pub = n.advertise<std_msgs::Float32>("my_topic" , 1000); 
    sub = n.subscribe("my_topic", 1000, recieve);
    ROS_INFO("Ready: Enter 9 matrix number for determinant!");
    ros::spin();
    
    return 0;
}



