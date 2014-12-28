#include "ws2812.h"
#include "ets_sys.h"
#include "mystuff.h"
#include "osapi.h"
#include "at_gpio.h"
#include "gpio.h"

//Through testing, I've found that these cause the pin to be at that state for time = 1/10th of a us. (plus 1/15?th of a us for the call)
static void WSON( uint8_t time )
{
	while(time--)
	{
		WRITE_PERI_REG( PERIPHS_GPIO_BASEADDR + GPIO_ID_PIN(WSGPIO), 1 );
	}
}

static void WSOFF( uint8_t time )
{
	while(time--)
	{
		WRITE_PERI_REG( PERIPHS_GPIO_BASEADDR + GPIO_ID_PIN(WSGPIO), 0 );
	}
}

#define SEND_WS_0 { WSON( 1 ); WSOFF( 8 ); }
#define SEND_WS_1 { WSON( 6 ); WSOFF( 3 ); }

void WS2812OutBuffer( uint8_t * buffer, uint16_t length )
{
	uint16_t i;
	GPIO_OUTPUT_SET(GPIO_ID_PIN(WSGPIO), 0);
	for( i = 0; i < length; i++ )
	{
		uint8_t byte = buffer[i];
		os_intr_lock();
		if( byte & 0x80 ) SEND_WS_1 else SEND_WS_0
		if( byte & 0x40 ) SEND_WS_1 else SEND_WS_0
		if( byte & 0x20 ) SEND_WS_1 else SEND_WS_0
		if( byte & 0x10 ) SEND_WS_1 else SEND_WS_0
		if( byte & 0x08 ) SEND_WS_1 else SEND_WS_0
		if( byte & 0x04 ) SEND_WS_1 else SEND_WS_0
		if( byte & 0x02 ) SEND_WS_1 else SEND_WS_0
		if( byte & 0x01 ) SEND_WS_1 else SEND_WS_0
		os_intr_unlock();
	}
	//reset will happen when it's low long enough.
	//(don't call this function twice within 10us)
}



