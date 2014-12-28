/*
 * Written By Hans
 * This is my first version of the driver for BH1750
 * I used few codes i found online to produce this
 * Big thanks who ever wrote the I2c Drivers
 */
#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "c_types.h"

#include "user_interface.h"
#include "BH1750.h"
#include "i2c/i2c.h"
#define BH1750address 0x23 //This is the Address for when add line Low
//#define BH1750address 0x5C //This is the Address for when add line High
//#define DEBUG

///////////////////////////////////////////////////////////////
//BH1750
///////////////////////////////////////////////////////////////
int ICACHE_FLASH_ATTR
test_light_sensor()
{
	#ifdef DEBUG
	char temp[128];
	uart0_sendStr("Test light started\r\n");
	#endif
    uint8 dtmp1,dtmp2;
    uint16 res;
    int data;
    i2c_init();
    BH1750Init();

	#ifdef DEBUG
    uart0_sendStr("first part done \n");
	#endif

    i2c_start();
    uint8 readAdd = BH1750address << 1; //shift the address
    readAdd = readAdd +0x1;				//add the read bit

    i2c_writeByte(readAdd);
    if (!i2c_check_ack())
    {
		#ifdef DEBUG
    	uart0_sendStr("data not ack 1 \n");
		#endif
        i2c_stop();
        return -1;
    }
    dtmp1=i2c_readByte();//read MSB
    i2c_send_ack(1);
    dtmp2=i2c_readByte();//read LSB
    i2c_send_ack(0);           //NACK READY FOR STOP
    i2c_stop();

    //start doing the calculation
     res=( (dtmp1<<8)|dtmp2 );
     data=(res*10)/12;  //CAL VALUE
	#ifdef DEBUG
     uart0_sendStr("Test light ended\r\n");
     os_sprintf(temp,"Value#: 0x%x ;%d ; %d ;%d \r\n\r\n",res,data,dtmp1,dtmp2);
     uart0_sendStr(temp);
	#endif
    return data;
}


void ICACHE_FLASH_ATTR BH1750Init(){
    i2c_start();
    i2c_writeByte(BH1750address << 1);
    if (!i2c_check_ack())
    {
		#ifdef DEBUG
    	uart0_sendStr("data not ack 1 \n");
		#endif
        i2c_stop();
        return;
    }
    i2c_writeByte(0x10);
    if (!i2c_check_ack())
    {
		#ifdef DEBUG
    	uart0_sendStr("failed at send data ack \n");
		#endif
        i2c_stop();
        return;
    }
    i2c_stop();
}

