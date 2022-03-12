#include <bits/stdc++.h>
#include <opencv2/opencv.hpp> 
#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <iostream>

using namespace std;
using namespace cv;

//publisher
ros::Publisher pub_cam_x;
ros::Publisher pub_cam_y;

//timer
ros::Timer timer_aja;

class photo{
    private :
    int x,y;

    public:
    void setCenterx(int xcen){
        x=xcen;
    }
    void setCentery(int ycen){
        y=ycen;
    }
    int getCenterX(){
        return x;
    }
    int getCenterY(){
        return y;
    }
};

photo ball;

void fungsi_callback (const ros::TimerEvent &event){
    std_msgs::Int16 x,y;
    x.data= ball.getCenterX();
    y.data= ball.getCenterY();
    pub_cam_x.publish(x);
    pub_cam_y.publish(y);
    // ROS_INFO("center %d %d", x.data, y.data);
}



//detect posisi bola (center)
//resize 1200x800
int main(int argc, char** argv) {
    ros::init(argc,argv, "node_cam");
    ros::NodeHandle nh;
    ros::MultiThreadedSpinner mts;

    Mat foto, foto_resize, foto_color, tresh;
    foto = imread("/home/ubuntu/final_project/src/beginner_tutorials/src/aset/8.jpg");
    resize (foto,foto_resize, Size(1200,800));
    cvtColor(foto_resize, foto_color, COLOR_BGR2HSV);     

    int L_H = 0;
    int U_H = 80;
    int L_S = 0;
    int U_S = 250;
    int L_V = 0;
    int U_V = 240;
    int xc,yc;


    inRange(foto_color, Scalar (L_H, L_S, L_V), Scalar(U_H, U_S, U_V), tresh);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(tresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    for (int i=0;i<contours.size();i++){
            vector<Point>contours_lagi;
            Point2f center;
            float radius;
            contours_lagi = contours[i];
            minEnclosingCircle(contours_lagi,center,radius);

            if (radius>=100 && radius <=150){
                xc=center.y;
                yc=center.x;
            }
    }

    ball.setCenterx(xc);
    ball.setCentery(yc);

    timer_aja = nh.createTimer(ros::Duration(0.2),fungsi_callback);

    pub_cam_x = nh.advertise<std_msgs::Int16>("posisi_target_x",16);
    pub_cam_y = nh.advertise<std_msgs::Int16>("posisi_target_y",16);

    mts.spin();

    }