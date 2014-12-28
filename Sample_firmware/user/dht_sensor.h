#ifndef _DHT_SENSOR_H_
#define _DHT_SENSOR_H_

#include "eagle_soc.h"
#include "gpio.h"

void dht_sensor_init(uint8 pgpio_id, uint32 pgpio_name, uint8 pgpio_func);
void dht_timerfunc(void *arg);

#define MAXTIMINGS 84
#define HIGHLEVEL 20

#endif
