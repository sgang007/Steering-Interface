#include <serial_lib.h>
#include <iostream>
#define PORT "/dev/ttyACM0"
int main(int argc, char const *argv[])
{
	long b=9600;
	serial_lib s(PORT);
	if (s.serialport_init(9600))
	{	
		int buf_max=14;
		char buff[buf_max];
		memset(buff,0,buf_max);
		std::cout<<"\nReading chars: ";
		std::cout<<s.serialport_read_until(buff,'\n',12,100);
		usleep(100);
		//std::cout<<buff[0]<<std::endl;		
		printf("%s\n", buff );
		//s.serialport_flush();
		s.serialport_close();	
	}
	
	/* code */
	return 0;
}