//
// arduino-serial-lib -- simple library for reading/writing serial ports
//
// 2006-2013, Tod E. Kurt, http://todbot.com/blog/
//



#ifndef __ARDUINO_SERIAL_LIB_H__
#define __ARDUINO_SERIAL_LIB_H__

// uncomment this to debug reads

#include <stdint.h>   // Standard types 
#include <stdio.h>   // Standard input/output definitions 
#include <unistd.h>   // UNIX standard function definitions 
#include <fcntl.h>    // File control definitions 
#include <errno.h>    // Error number definitions 
#include <termios.h>  // POSIX terminal control definitions 
#include <string.h>   // String function definitions 
#include <sys/ioctl.h>

class serial_lib
{
private:
	int fd;
public:
	serial_lib(const char* serialport);
	bool serialport_init(int baud);
	int serialport_close();
	int serialport_writebyte(uint8_t b);
	int serialport_write(const char* str);
	int serialport_read_until(char* buf, char until, int buf_max,int timeout);
	int serialport_flush();
	//~serial_lib();
	
};


#endif

