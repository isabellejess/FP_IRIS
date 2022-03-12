#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <functional>

//subscriber
ros::Subscriber sub_pc_x;
ros::Subscriber sub_pc_y;
ros::Subscriber sub_pc_vx;
ros::Subscriber sub_pc_vy;
ros::Subscriber sub_pc_thetaf;
ros::Subscriber sub_pc_omega;

//timer
ros::Timer timer_aja;

class motor{
    private:
    int x,y,xf,yf,vx,vy,theta,thetaf,omega,t;

    public:
    void setPosisiawal (int eks,int ye){
        x=eks;
        y=ye;
    }
    int getAwalx (){
        return x;
    }
    int getAwaly (){
        return y;
    }
    void setThetaawal (int teta){
        theta=teta;
    }
    int getThetaawal(){
        return theta;
    }
    void setXakhir (int xx){
        xf=xx;
    }
    int getXakhir(){
        return xf;
    }
    void setYakhir (int yy){
        yf=yy;
    }
    int getYakhir(){
        return yf;
    }
    void setThetaf (int tf){
        thetaf=tf;
        if (thetaf>180){
            thetaf=180-thetaf;
        }
    }
    int getThetaf(){
        return thetaf;
    }
    void setvx (int vxx){
        vx=vxx;
    }
    int getvx(){
        return vx;
    }
    void setvy (int vyy){
        vy=vyy;
    }
    int getvy(){
        return vy;
    }
    void setOmega (int om){
        omega=om;
    }
    int getOmega(){
        return omega;
    }
    void setPosisi(int tumbal){
        if (x<xf){
            x=x+vx;
            if (x>=xf){
                x=xf;
            }
        }
        if (y<yf){
            y=y+vy;
            if (y>=yf){
                y=yf;
            }
        }

    }

    void setTheta(int tumbal){
        if (theta<thetaf){
            theta=theta+omega;
            if (theta>thetaf){
                theta=thetaf;
            }
        }
        else{
            theta=theta-omega;
            if (theta<thetaf){
                theta=thetaf;
            }
        }
    }
    int getPosisix (){
        return x;
    }
    int getPosisiy (){
        return y;
    }
    int getPosisiTheta (){
        return theta;
    }
    void cek(int tumbal){
        t=tumbal;
        if (((x==xf) && (y==yf)) && (theta==thetaf)){
            t=1;
        }
    }
    int getT(){
        return t;
    }
};

motor p;
std_msgs::Int16 x,y,vx,vy,xf,yf,theta,thetaf,omega,t;

void callback_x (const std_msgs::Int16 &msg){
    p.setXakhir(msg.data);
}
void callback_y (const std_msgs::Int16 &msg){
    p.setYakhir(msg.data);
}
void callback_vx (const std_msgs::Int16 &msg){
    p.setvx(msg.data);
}
void callback_vy (const std_msgs::Int16 &msg){
    p.setvy(msg.data);
}
void callback_thetaf (const std_msgs::Int16 &msg){
    p.setThetaf(msg.data);
}
void callback_omega (const std_msgs::Int16 &msg){
    p.setOmega(msg.data);
}

void fungsi_callback (const ros::TimerEvent &event){
    ROS_INFO("x=%d, ",x.data);
    ROS_INFO("y=%d, ",y.data);
    ROS_INFO("sudut=%d\n",theta.data);
    t.data=p.getT();
    if (t.data==1){
        ros::shutdown();
    }
    p.setPosisi(1);
    p.setTheta(1);
    x.data=p.getPosisix();
    y.data=p.getPosisiy();
    theta.data=p.getPosisiTheta();
    p.cek(0);

    
}

int main(int argc, char **argv){
    ros::init(argc,argv, "node_motor");
    ros::NodeHandle nh;
    ros::MultiThreadedSpinner mts;

    sub_pc_x = nh.subscribe("posisi_akhir_x", 16, callback_x);
    sub_pc_y = nh.subscribe("posisi_akhir_y", 16, callback_y);
    sub_pc_vx = nh.subscribe("kec_x", 16, callback_vx);
    sub_pc_vy = nh.subscribe("kec_y", 16, callback_vy);
    sub_pc_thetaf = nh.subscribe("sudut_akhir", 16, callback_thetaf);
    sub_pc_omega = nh.subscribe("kec_tan", 16, callback_omega);

    timer_aja = nh.createTimer(ros::Duration(0.5),fungsi_callback);
    p.setPosisiawal(0,0);
    p.setThetaawal(0);

    mts.spin();
}