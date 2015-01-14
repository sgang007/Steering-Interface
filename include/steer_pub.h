#ifndef __STEER_PUB_H__
#define __STEER_PUB_H__

#define STEERING_DEBUG

#include "serial_lib.h"
#include "crc16.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <math.h>
#include <cctype>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//generate steering angle and steering angle velocity
class steering_encoder
{
	private:
		char* packet;
		serial_lib *serialConnection;
	public:
		steering_encoder();
		void get_steer_values(float &ang, float &ang_change); //calculate steering angles and velocities by combining hb and lb
		float handwheel_to_steering(bool radians=false); //convert angle to actual_steering_angle
		bool crc_check(); //check crc validity for packet
		void read_packet();	//read data from serial port
		
};
#endif
