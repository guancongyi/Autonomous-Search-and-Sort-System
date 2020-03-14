/* ************************************************************************** */
/** 
  @File Name
    sensor_state.h

  @Summary
 * The interface of the 5-stage FSM


 */
/* ************************************************************************** */

#include "FreeRTOS.h"
#include "queue.h"
#include <stdio.h>
#include <math.h>

// The five status of the FSM    
typedef enum
{
	STATE_1=1, STATE_2, STATE_3, STATE_4, STATE_5
} SENSOR_STATE;



// This function will be used to calculate the average of the sensor value.
void Five_State_FSM(uint8_t SENSOR_VAL, double *average, SENSOR_STATE *state);

