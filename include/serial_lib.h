//
// arduino-serial-lib -- simple library for reading/writing serial ports
//
// 2006-2013, Tod E. Kurt, http://todbot.com/blog/
//


#ifndef __ARDUINO_SERIAL_LIB_H__
#define __ARDUINO_SERIAL_LIB_H__

#include <stdint.h>   // Standard types 

class serial_lib{
	private:
		int fd;
	public:
		serial_lib();
		bool isInitialized() ;
		int serialport_init(const char* serialport, int baud);
		int serialport_close();
		int serialport_writebyte( uint8_t b);
		int serialport_write( const char* str);
		int serialport_read_until( char* buf, char until, int buf_max,int timeout);
		int serialport_flush();


};
#endif

