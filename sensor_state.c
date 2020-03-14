/* ************************************************************************** */
/** Descriptive File Name
  @File Name
    sensor_state.c

  @Summary
 * The implementation of the 5-stages FSM



/* TODO:  Include other files here if needed. */
#include "sensor_state.h"
#include "debug.h"
#include "app.h"
// This function will pass the State parameter and average parameter by refernce
// It functionality is to calculate the average of the sensor value
void Five_State_FSM(uint8_t SENSOR_VAL, double *average, SENSOR_STATE *state) {
    switch(*state) {
        case STATE_1:
            *average = 0;
          //  dbgOutputLoc(ENTER_FSM_STATE_ONE);
            dbgOutputVal(SENSOR_VAL);
            *average = *average + SENSOR_VAL;
            *state = STATE_2;
            break;
        case STATE_2:
         //   dbgOutputLoc(ENTER_FSM_STATE_TWO);
            dbgOutputVal(SENSOR_VAL);
            *average = *average + SENSOR_VAL;
            *state = STATE_3;
            break;
        case STATE_3:
         //   dbgOutputLoc(ENTER_FSM_STATE_THREE);
            dbgOutputVal(SENSOR_VAL);
            *average = *average + SENSOR_VAL;
            *state = STATE_4;
            break;
        case STATE_4:
           // dbgOutputLoc(ENTER_FSM_STATE_FOUR);
            dbgOutputVal(SENSOR_VAL);
            *average = *average + SENSOR_VAL;
            *state = STATE_5;
            break;
        case STATE_5:
            //dbgOutputLoc(ENTER_FSM_STATE_FIVE);
            *average = (*average + SENSOR_VAL) / 5.0;
            dbgOutputVal(SENSOR_VAL);
            //dbgUARTVal(average);
            *state = STATE_1;
            char distance[20];
            sprintf(distance,"%f",*average);
            dbgUARTVal(distance);
            break;
        default:
            //dbgStopCode(true);
            break;
    }
}


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
int ExampleInterfaceFunction(int param1, int param2) {
    return 0;
}


/* *****************************************************************************
 End of File
 */
