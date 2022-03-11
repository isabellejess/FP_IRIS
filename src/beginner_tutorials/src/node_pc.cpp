//nangkep data cam
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp> 
#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <iostream>

//publisher
ros::Publisher pub_pc_x;
ros::Publisher pub_pc_y;
ros::Publisher pub_pc_sudut;

//subscriber
ros::Subscriber sub_cam;

//timer
ros::Timer timer_aja;

class pc{
    private:
    int x,y,xf,yf,vx,vy,omega,theta,thetaf;

    public:
    void atur (int kecx, int kecy){
        vx=kecx;
        vy=kecy;
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
    int getOmega(){
        return omega;
    }


    void setPosisi(int a, int b){
        int xf, yf;
        while(ros::ok()){
            ros::spinOnce();
            if (b>=a){
            for (int i=0;i<y;i++){
                for (int j=0;j<x;j++){
                    a=a+vx;
                    }
                }
            }
            else{
                for (int j=0;j<x;j++){
                    for (int i=0;i<y;i++){
                        b=b+vy;
                    }
                }
            }
            x=a;
            y=b;
            if (x==xf && y==yf){
                ros::shutdown();
            }
        }
    }
    
    int getPosisix(){
        return x;
    }
    int getPosisiy(){
        return y;
    }
    void setTheta (int thet, int vtan){
        ros::spinOnce();
        omega=vtan;
        if (thet>180){
            thet=180-thet;
        }
        if (thet!=thetaf){
            thet=thet+omega;
        }   
    }
    int getTheta(){
        return theta;
    }

};

pc pic;
void fungsi_callback (const ros::TimerEvent &event){
    std_msgs::Int16 x;
    std_msgs::Int16 y;
    std_msgs::Int16 theta;
    x.data=pic.getPosisix();
    y.data=pic.getPosisiy();
    theta.data=pic.getTheta();
    pub_pc_x.publish(x);
    pub_pc_y.publish(y);
    pub_pc_sudut.publish(theta);
    //ROS_INFO("nyoba %d %d %d",x.data,y.data,theta.data);
}

void callback_cam_x (const std_msgs::Int16 &msg){
    std_msgs::Int16 xcen;
    pic.setCenterx(msg.data);
}
void callback_cam_y (const std_msgs::Int16 &msg){
    std_msgs::Int16 ycen;
    pic.setCentery(msg.data);
}

int main(int argc, char **argv){
    ros::init(argc,argv, "node_pc");
    ros::NodeHandle nh;
    ros::MultiThreadedSpinner mts;

    pic.atur(2,3);

    pic.getCenterx();
    pic.getCentery();
    pic.setPosisi(0,0);
    pic.setTheta(0,4);
    pic.setThetaf(60);
    pic.getThetaf();
    pic.getOmega();
    

    sub_cam = nh.subscribe("posisi_target", 16, callback_cam_x);
    sub_cam = nh.subscribe("posisi_target", 16, callback_cam_y);

    timer_aja = nh.createTimer(ros::Duration(0.5),fungsi_callback);
    pub_pc_x = nh.advertise<std_msgs::Int16>("posisi_x",16);
    pub_pc_y = nh.advertise<std_msgs::Int16>("posisi_y",16);
    pub_pc_sudut = nh.advertise<std_msgs::Int16>("posisi_sudut",16);


    mts.spin();
}

