#include "serial_lib.h"
#include "crc16.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <math.h>
#include <cctype>
#include <stdint.h>

//generate steering angle and steering angle velocity
class steering_encoder
{
	private:
		float angle;//handwheel angles
		float angle_change; //handwheel angle change
		float time_step;
	public:
		steering_encoder();
		void get_steer_values(char *packet); //calculate steering angles and velocities by combining hb and lb
		float handwheel_to_steering(bool radians=false); //convert angle to actual_steering_angle
		bool crc_valid(char *packet); //check crc validity for packet
		bool read_packet();	//read data from serial port
		void* generate_message(); //generate msg object of std_msgs/Float type
};
