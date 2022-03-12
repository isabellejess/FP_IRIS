//nangkep data cam
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp> 
#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <iostream>

//publisher
ros::Publisher pub_pc_x;
ros::Publisher pub_pc_y;
ros::Publisher pub_pc_vx;
ros::Publisher pub_pc_vy;
ros::Publisher pub_pc_thetaf;
ros::Publisher pub_pc_omega;

//subscriber
ros::Subscriber sub_cam_x;
ros::Subscriber sub_cam_y;

//timer
ros::Timer timer_aja;


class pc{
    private:
    int xf,yf,vx,vy,omega,thetaf;

    public:
    void atur (int kecx, int kecy){
        vx=kecx;
        vy=kecy;
    }
    int getAturx(){
        return vx;
    }
    int getAtury(){
        return vy;
    }
    void setCenterx (int xc){
        xf=xc;
    }
    int getCenterx(){
        return xf;
    }
    void setCentery (int yc){
        yf=yc;
    }
    int getCentery(){
        return yf;
    }
    void setThetaf(int sudut){
        thetaf=sudut;
    }
    int getThetaf(){
        return thetaf;
    }
    void setOmega(int sudut){
        omega=sudut;
    }
    int getOmega(){
        return omega;
    }
};

pc pic;
    
void callback_cam_x (const std_msgs::Int16 &msg){
    pic.setCenterx(msg.data);
}
void callback_cam_y (const std_msgs::Int16 &msg){
    pic.setCentery(msg.data);
}
void fungsi_callback (const ros::TimerEvent &event){
    std_msgs::Int16 x,y,vx,vy,theta,omega;
    x.data=pic.getCenterx();
    y.data=pic.getCentery();
    vx.data=pic.getAturx();
    vy.data=pic.getAtury();
    theta.data=pic.getThetaf();
    omega.data=pic.getOmega();
    pub_pc_x.publish(x);
    pub_pc_y.publish(y);
    pub_pc_vx.publish(vx);
    pub_pc_vy.publish(vy);
    pub_pc_thetaf.publish(theta);
    pub_pc_omega.publish(omega);
    //ROS_INFO("tes %d %d %d %d %d %d\n",x.data,y.data,vx.data,vy.data,theta.data,omega.data);
}

int main(int argc, char **argv){
    ros::init(argc,argv, "node_pc");
    ros::NodeHandle nh;
    ros::MultiThreadedSpinner mts;
    sub_cam_x = nh.subscribe("posisi_target_x", 16, callback_cam_x);
    sub_cam_y = nh.subscribe("posisi_target_y", 16, callback_cam_y);
    pub_pc_x = nh.advertise<std_msgs::Int16>("posisi_akhir_x",16);
    pub_pc_y = nh.advertise<std_msgs::Int16>("posisi_akhir_y",16);
    pub_pc_vx = nh.advertise<std_msgs::Int16>("kec_x",16);
    pub_pc_vy = nh.advertise<std_msgs::Int16>("kec_y",16);
    pub_pc_thetaf = nh.advertise<std_msgs::Int16>("sudut_akhir",16);
    pub_pc_omega = nh.advertise<std_msgs::Int16>("kec_tan",16);
    timer_aja = nh.createTimer(ros::Duration(0.2),fungsi_callback);

    pic.atur(96,67);
    pic.setThetaf(263);
    pic.setOmega(17);
    
    mts.spin();
}