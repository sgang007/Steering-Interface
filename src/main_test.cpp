//#define GET_IP_FROM_FILE 1
//#define DEFAULT_IP "10.7.16.210"

#include <steer_pub.h>
#include <ros.h>
#include <std_msgs/Float64.h>
#define MSG_PATH "/interfaces/encoder/steering"

 ros::NodeHandle steering_pub;
 std_msgs::Float64 msg;


ros::Publisher st_encoder(MSG_PATH, &msg);


 char *rosSrvrIP=(char*)"10.7.16.210";

int main(int argc, char** argv)
{   
#if GET_IP_FROM_FILE == 1

    FILE *fp = fopen("/opt/rosserial/bin/RosSrvrIp", "r");
    
    // Check that we opened the file correctly
    if(fp == NULL)
       printf("Using default IP DEFAULT_IP : /opt/rosserial/bin/RosSrvrIp not found\n");    
    else
    {
        fscanf(fp, "%s", &rosSrvrIp);
        printf("Using /opt/rosserial/bin/RosSrvrIp IP %s\n",rosSrvrIp);
        fclose(fp);
    }  
#endif  
    float angle=0.0,angle_change=0.0;
    steering_encoder stencdr_obj;
    steering_pub.initNode(rosSrvrIP);
    steering_pub.advertise(st_encoder);
    while(1)
    {
        stencdr_obj.read_packet();
        //if(stencdr_obj.crc_check())
        stencdr_obj.get_steer_values(angle,angle_change);       
        msg.data=angle;
        st_encoder.publish(&msg);
        steering_pub.spinOnce();    
    }

    return 0;
}