
/*
#include "c_types.h"
#include "ets_sys.h"
#include "eagle_soc.h"
#include "gpio.h"
#include "uart.h"
#include "string.h"
#include "BH1750.h"
*/
#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "c_types.h"

#include "user_interface.h"
#include "BH1750.h"
#include "i2c_master.h"

#define i2c_start i2c_master_start
#define i2c_writeByte i2c_master_writeByte
#define i2c_getAck i2c_master_getAck
//#define ets_printf os_printf
#define i2c_stop i2c_master_stop
#define ets_delay_us os_delay_us
#define i2c_readByte i2c_master_readByte
#define i2c_setAck i2c_master_setAck



///////////////////////////////////////////////////////////////
//BH1750
///////////////////////////////////////////////////////////////
int ICACHE_FLASH_ATTR
test_light_sensor()
{
    uint8 ack;
    uint8 dtmp1,dtmp2;
    uint16 res;
    int data;
    i2c_start();
    i2c_writeByte(0x46+0); // sensor address  + write bit
        if(i2c_getAck() )
        {
            os_printf("addr not ack r \n");
            i2c_stop();
            return;
        }
    i2c_writeByte(0x23); // config one time L-resolution mode
        if(i2c_getAck() )
        {
            os_printf("data not ack 1 \n");
            i2c_stop();
            return;
        }
    i2c_stop();
    ets_delay_us(30000);//  wait measure time, 24ms at most
    i2c_start();
    i2c_writeByte(0x46+0x1);//  sensor address + read bit
            if(i2c_getAck() )
        {
            os_printf("addr not ack w \n");
            i2c_stop();
            return;
        }
     dtmp1=i2c_readByte();//read MSB
     i2c_setAck(0);
     dtmp2=i2c_readByte();//read LSB
     i2c_setAck(1);           //NACK READY FOR STOP
     i2c_stop();
     res=( (dtmp1<<8)|dtmp2 );
     data=(res*10+6)/12;  //CAL VALUE
     os_printf("light sensor reg: 0x%x ;  val : %d [lx] \n\n",res,data);
    return data;

}




