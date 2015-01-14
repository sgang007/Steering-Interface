#include <steer_pub.h>

//#include <std_msgs/Float.h>
#define SER_PORT "/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_95335343136351612280-if00"
#define BAUD_RATE 9600
#define BUFFER_SIZE 11
#define BUS_ID 301
#define TIMEOUT 10
#define TIMESTEP 10.0/1000.0 //duration between messages in seconds
using namespace std;

inline void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}
steering_encoder::steering_encoder()
{
	packet=new char[256];	
	serialConnection=new serial_lib();
	if (serialConnection->isInitialized())
		serialConnection->serialport_close();
	serialConnection->serialport_init(SER_PORT,BAUD_RATE);

    if(!serialConnection->isInitialized())
    	error((char *)"Couldn't open port");
#ifdef STEERING_DEBUG    
	 printf("Opened port %s\n",SER_PORT);
#endif
    serialConnection->serialport_flush();
}

float handwheel_to_steering(bool radians=false)
{
	//mapping between steering and handwheel after profiling system
}
bool steering_encoder::crc_check()
{
	int length=packet[0];
	char new_pac[length-2]; //the last two bytes are crc bytes
	//shifting data to left by 1
	for(int i=0;i<length-2;i++)
		new_pac[i]=packet[i+1];
	return crc_valid(hextoi(packet[length],packet[length-1]),new_pac,length-2);
}
void steering_encoder::read_packet()
{
	char eolchar='\n';
	int timeout=5000;
	const int buf_max = 256;
	char buf[buf_max];   

	if( !serialConnection->isInitialized())
	{
		error((char *)"serial port not opened");
	
	}
    memset(buf,0,buf_max);  //sets packet to 256 0s
    serialConnection->serialport_read_until( buf, eolchar, buf_max, timeout);
#ifdef STEERING_DEBUG
    printf("\nReceived string: %s",buf);
#endif
    for (int i=0;i<buf_max;i++)
    {
    	if (buf[1]!=0)
    		packet[i]=buf[i];
    	else
    		break;
    }	
    
}

int hextoi(char hb,char lb)
{
     
    unsigned int unsigned_temp= int(hb)*256+int(lb);
	int signed_temp = (int16_t) unsigned_temp;
	return signed_temp;
}


void steering_encoder::get_steer_values(float &angle,float &angle_vel)
{
	 angle=(((float)hextoi(packet[2],packet[1])*359.912)/4095.0);
	 angle_vel=(((float)hextoi(packet[2],packet[1])*359.912)/4095.0)/TIMESTEP;
#ifdef STEERING_DEBUG
	 printf("\nSteering angle:%f\n",angle);
#endif
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