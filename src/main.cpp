#include <steer_pub.h>

int main(int argc, char** argv)
{
    //char s[]="2 / 8 / 301 / 38 / 3 / E1 / 0 / 0 / 15 / B7 / 4B";
    int fd=serialport_init("/dev/ttyACM0",115200);
    char buf[11];
    if(serialport_read_until(fd,buf,'\n',11,10)!=-1)
    for(int i=0;i<11;i++)
    {   
        if (buf[i]==0 || buf[i]=='\n')
            break;
        cout<<buf[i]<<',';
    }
    serialport_close(fd);
	char frame_data[8],frame_data_crc[6];
	frame_data[0] = 0x38;
	frame_data[1] = 0x03;
	frame_data[2] = 0xE1;
	frame_data[3] = 0x00;
	frame_data[4] = 0x00;
	frame_data[5] = 0x15;
	frame_data[6] = 0xB7;
	frame_data[7] = 0x4B;
    
    for(int i=0;i<6;i++)
		frame_data_crc[i]=frame_data[i];
    char crcval[2];

    
    cout<<"\ncrc gen:"<<dec<<crc16 (frame_data, 6)<<endl;
    cout<<"crc got:"<<dec<<hextoi(frame_data[7],frame_data[6])<<endl;
    if (crc_valid(hextoi(frame_data[7],frame_data[6]),frame_data_crc,6))
        std::cout<<"Hooray";
	cout<<dec<<"Steering Angle = "<<double(hextoi(frame_data[1],frame_data[0]))*359.912/4095<<endl;
	cout<<"Count  = "<<hextoi(0x00,frame_data[2])<<endl;
	cout<<"Steering Angle Change= "<<double(hextoi(frame_data[4],frame_data[3]))*359.912/4095<<endl;
	cout<<"Status= "<<hextoi(0x00,frame_data[5])<<endl;
    

    return 0;
}