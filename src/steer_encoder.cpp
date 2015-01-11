#include <steer_pub.h>
#include <std_msgs/Float.h>
#define SER_PORT "/dev/ttyACM0"
#define BAUD_RATE 115200
#define BUFFER_SIZE 11
#define BUS_ID 301
#define TIMEOUT 10

using namespace std;

steering_encoder::steering_encoder()
{
	angle=0.0;
	angle_change=0.0;
	time_step=10.0;
}
float handwheel_to_steering(bool radians=false)
{
	//mapping between steering and handwheel after profiling system
}
bool steering_encoder::crc_valid(char *packet)
{

}
bool steering_encoder::read_packet(char *packet)
{
	serial_lib s(SER_PORT);
	if (s.serialport_init(BAUD_RATE))
	{
		if(s.serialport_read_until(packet,'\n',BUFFER_SIZE,TIMEOUT)==0)
			return true;
	}
	return false;
}

int hextoi(char hb,char lb)
{
     
    unsigned int unsigned_temp= int(hb)*256+int(lb);
	int signed_temp = (int16_t) unsigned_temp;
	return signed_temp;
}


void steering_encoder::get_steer_values(char *packet)
{

}

void* steering_encoder::generate_message()
{
	//create object of msg type;
	//populate the message;
	//return pointer to object
}

/*
 * Interface: CAN 2.0 B

Baud rate: 125 kBaud, 250 kBaud (default), 500 kBaud

SASA returns cyclic the following CAN message every 5, 10 (default) or 20 ms.

ID Steering angle Count Steering angle change Status CRC-16

Identifier: 301h (11 bit)

Steering angle: 12 bit word (0 – 4095) relative to a 0-index point.

4095 = 359,912 degrees

Overflow at 4095 for CW activation shall increment 0

Underflow at 0 for CCW activation shall decrement 4095

Count: byte (0-255)

Steering angle

change:

Increments 1 for each message

Difference between 2 transmitted position values in succession.

16 bit integer with 2’s complementary encoding for negative values (-32768 to

32767).

-4095 = -359.912 degrees

0 = 0 degrees

4095 = 359,912 degrees
* */
