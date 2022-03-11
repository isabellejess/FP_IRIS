#include "ros/ros.h"
#include "std_msgs/Int16.h"

//subscriber
ros::Subscriber sub_pc_x;
ros::Subscriber sub_pc_y;
ros::Subscriber sub_pc_sudut;

//timer
ros::Timer timer_aja;

class tampil{
    private:
    int x,y,theta;

    public:
    void setPosisix (int eks){
        x=eks;
    }
    int getPosisix (){
        return x;
    }

    void setPosisiy (int ye){
        y=ye;
    }
    int getPosisiy (){
        return y;
    }

    void setPosisiTheta (int teta){
        theta=teta;
    }
    int getPosisiTheta(){
        return theta;
    }
};

tampil pic;
std_msgs::Int16 x,y,theta;

void fungsi_callback (const ros::TimerEvent &event){
    std_msgs::Int16 x,y,theta;
    x.data=pic.getPosisix();
    y.data=pic.getPosisiy();
    theta.data=pic.getPosisiTheta();

    ROS_INFO("x=%d, ",x.data);
    ROS_INFO("y=%d, ",y.data);
    ROS_INFO("sudut=%d\n",theta.data);
}

void callback_x (const std_msgs::Int16 &msg){
    std_msgs::Int16 nih_x;
    pic.setPosisix(msg.data);
}
void callback_y (const std_msgs::Int16 &msg){
    std_msgs::Int16 nih_y;
    pic.setPosisiy(msg.data);
}
void callback_sudut (const std_msgs::Int16 &msg){
    std_msgs::Int16 nih_theta;
    pic.setPosisiTheta(msg.data);
}


int main(int argc, char **argv){
    ros::init(argc,argv, "node_motor");
    ros::NodeHandle nh;
    ros::MultiThreadedSpinner mts;

    sub_pc_x = nh.subscribe("posisi_x", 16, callback_x);
    sub_pc_y = nh.subscribe("posisi_y", 16, callback_y);
    sub_pc_sudut = nh.subscribe("posisi_sudut", 16, callback_sudut);

    timer_aja = nh.createTimer(ros::Duration(0.5),fungsi_callback);

    mts.spin();
}

