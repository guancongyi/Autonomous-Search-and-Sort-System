#ifndef _SENSOR_THREAD_H 
#define _SENSOR_THREAD_H 
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "debug.h"
void Sensor_Tasks( void );
MotorStatus_ ReceiveMessage_();

#endif 