/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "sensor_state.h"
#include <stdio.h>
#include <math.h>
#include "sensor_queue.h"
#include "debug.h"
#include "timers.h"
#include "JSON.h"
#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")
void APP_Initialize ( void )
{
}


void setMotorSpeed(MotorStatus_ *motor, int leftSpeed, int rightSpeed) {
    motor->left_motor_desired_wheel_speed = leftSpeed;
    motor->right_motor_desired_wheel_speed = rightSpeed;
}
void setDirection(MotorStatus_ *motor, int Direction) {
    motor->direction = Direction;
    if (Direction == 0) {
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
    }
    else if (Direction == 1) {
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
    }
    else if (Direction == 2) {
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
        PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
    }
    else {
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
    }
}
void setDistance(MotorStatus_ *motor, int leftDistance, int rightDistance) {
    motor->left_distance = leftDistance;
    motor->right_distance = rightDistance;
}
void setDistance2(MotorStatus_ *motor, int leftDistance, int rightDistance) {
    motor->left_distance = leftDistance;
    motor->right_distance = rightDistance;
}
void dbgUARTVal2(char *outVal)
{

    SendUART_TRANSMIT_Message(outVal);
    if (!SYS_INT_SourceIsEnabled(INT_SOURCE_USART_1_TRANSMIT)) {
        SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
    }
    //SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
    
//	int i = 0;
//	for (i = 0; i < strlen(outVal); i++)
//	{
//        //SendUART_TRANSMIT_Message(outVal[i]);
//        //SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
//        
//		while (PLIB_USART_TransmitterBufferIsFull(USART_ID_1))
//		{
//   
//		}
//		PLIB_USART_TransmitterByteSend(USART_ID_1, outVal[i]);
//	}
};
void sendMessage_and_Reset(MotorStatus_ *Motor) {
    char check = 'T';
    BaseType_t pxHigherPriorityTaskWoken2 = pdFALSE;
    BaseType_t success;
    Incremental_PI2(ZERO,ZERO,ZERO);
    Incremental_PI1(ZERO,ZERO,ZERO);
    DRV_TMR1_CounterClear();
    DRV_TMR2_CounterClear();
    dbgOutputLoc(SW_ISR_SEND_START);
    //success = SendSensor_ISR_MessageFromISR(&check,  pxHigherPriorityTaskWoken2);
    success = SendSensor_ISR_MessageFromISR(Motor,  pxHigherPriorityTaskWoken2);
    if (success == pdFALSE) {
        dbgStopCode(SW_ISR_SEND_ERROR); 
    }
    dbgOutputLoc(SW_ISR_SEND_DONE);
    portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken2);
}
void send_Message_Uncomplete(MotorStatus_ *Motor){
    char check = 'F';
    BaseType_t pxHigherPriorityTaskWoken2 = pdFALSE;
    BaseType_t success;
    dbgOutputLoc(SW_ISR_SEND_START);
    success = SendSensor_ISR_MessageFromISR(Motor,  pxHigherPriorityTaskWoken2);
    if (success == pdFALSE) {
        dbgStopCode(SW_ISR_SEND_ERROR); 
    }
    dbgOutputLoc(SW_ISR_SEND_DONE);
    portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken2);
}

//0.013623188 cm per tick
//To rotate 90 degree, the rover need to move forward/backward 9.075cm => 636 ticks
void prvAutoReloadTimerCallback( TimerHandle_t xTimer ) {
    int counter1 = DRV_TMR1_CounterValueGet();
    int counter2 = DRV_TMR2_CounterValueGet();
    BaseType_t pxHigherPriorityTaskWoken2 = pdFALSE;
    TAG_UNION command;
    command.Mode = SPEED;
    command.Left_Motor_Encoder = counter2;
    command.Right_Motor_Encoder = counter1;
    SendMotorMessageFromISR(&command, pxHigherPriorityTaskWoken2);
    DRV_TMR1_CounterClear();
    DRV_TMR2_CounterClear();
    portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken2);
}


void APP_Tasks ( void )
{
    dbgOutputLoc(ENTERING_TASK);
    
    TimerHandle_t xAutoReloadTimer; 
    BaseType_t xTimer1Started;
    BaseType_t check;
    BaseType_t pxHigherPriorityTaskWoken2 = pdFALSE;
    BaseType_t success;
    xAutoReloadTimer = xTimerCreate( 
            "AutoReload", 
            mainAUTO_RELOAD_TIMER_PERIOD
            ,pdTRUE,
            (void *)ZERO, 
            prvAutoReloadTimerCallback );   
    dbgOutputLoc(BEFORE_WHILE);
    MotorStatus_ MotorStatus;
    int Sequence = 0;
    int num = 0;
    int Left;
    int Right;
    int direction;
    int Left_Travel;
    int Right_Travel;
    int Left_Desired_Speed;
    int Right_Desired_Speed;
    int counter1;
    int counter2;
    xTimer1Started =  xTimerStart( xAutoReloadTimer, ZERO ); 
    //success = SendSensor_ISR_MessageFromISR(&MotorStatus,  pxHigherPriorityTaskWoken2);
    //MOTOR_STATE state = SEND_GET_REQUEST;
    MOTOR_STATE state = LOCATE_OBJECT;
    while (1) {   
        TAG_UNION command;
        dbgOutputLoc(MOTOR_TASK_RECEIVE_FROM_QUEUE_START);
        check = ReceiveMotorMessage(&command); 
        dbgOutputLoc(MOTOR_TASK_RECEIVE_FROM_QUEUE_DONE);
        if (check != pdTRUE) {
            dbgStopCode(MOTOR_MESSAGE_QUEUE_RECEIVE_ERROR); 
        }
        switch(state){
            case LOCATE_OBJECT:
                if (command.Mode == LOCATE && command.Color_Stuff == 1) {
                    state = SEND_GET_REQUEST;
                    Incremental_PI2(ZERO,ZERO,ZERO);
                    Incremental_PI1(ZERO,ZERO,ZERO);
                }
                else {
                    if (command.Mode == SPEED) {
                        counter1 = command.Right_Motor_Encoder;
                        counter2 = command.Left_Motor_Encoder;
                        setDirection(&MotorStatus, 1);
                        Incremental_PI2(counter2,SEARCHING_SPEED,1);
                        Incremental_PI1(counter1,SEARCHING_SPEED,1);
                    }
                    sendRequest3(Pixel,1,0, 0, 0, 0, 0,0,0,0,0);
                }
                break;
            case SEND_GET_REQUEST:
                if  (command.Mode == MOTOR && command.Left_Motor_Distance > 0 && command.Right_Motor_Distance > 0) {
                    state = PROCESS_REQUEST;
                    direction = command.Motor_Direction;
                    Left_Travel = command.Left_Motor_Distance;
                    Right_Travel = command.Right_Motor_Distance;
                    Left_Desired_Speed = command.Left_Motor_Desired_Speed;
                    Right_Desired_Speed = command.Right_Motor_Desired_Speed;
                    if (command.Motor_Direction == 0) {
                        setDirection(&MotorStatus, 0);
                        Left = 0;
                        Right = 0;
                    }
                    else if (command.Motor_Direction == 1) {
                        setDirection(&MotorStatus, 1);
                        Left = 1;
                        Right = 0;
                    }
                    else if (command.Motor_Direction == 2) {
                        setDirection(&MotorStatus, 2);
                        Left = 0;
                        Right = 1;
                    }
                    else {
                        setDirection(&MotorStatus, 3);
                        Left = 1;
                        Right = 1;
                    }
                }
                else {
                    sendRequest3(Sensor,1,0, 0, 0, 0, 0,0,0,0,0);
                }
                break;
            case PROCESS_REQUEST:
                counter1 = command.Right_Motor_Encoder;
                counter2 = command.Left_Motor_Encoder;
                Left_Travel -= counter2;
                Right_Travel -= counter1;
                sendRequest3(Motor,0,direction, counter2, counter1, Left_Travel, Right_Travel,0,0,0,0);
                if (Left_Travel == ZERO && Right_Travel ==ZERO) {
                    state = LOCATE_OBJECT;
                    Incremental_PI2(ZERO,ZERO,ZERO);
                    Incremental_PI1(ZERO,ZERO,ZERO);
                }
                else {
                    if (Left_Travel > ZERO) {
                        Incremental_PI2(counter2,Left_Desired_Speed,1);
                    }
                    else if (Left_Travel == ZERO) {
                        Incremental_PI2(ZERO,ZERO,ZERO);
                    }
                    else {
                        Incremental_PI2(ZERO,ZERO,ZERO);
                        Left_Travel = -Left_Travel;
                        Left_Desired_Speed = LOWEST_SPEED;
                        Left = 1 - Left;
                        if (Left == 0) {
                            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
                            PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
                        }
                        else {
                            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
                            PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1);
                        }
                    }
                    if (Right_Travel > ZERO) {
                        Incremental_PI1(counter1,Right_Desired_Speed,1);
                    }
                    else if (Right_Travel == ZERO) {
                        Incremental_PI1(ZERO,ZERO,ZERO);
                    }
                    else {
                        Incremental_PI1(ZERO,ZERO,ZERO);
                        Right_Travel = -Right_Travel;
                        Right_Desired_Speed = LOWEST_SPEED;
                        Right = 1 - Right;
                        if (Right == 0) {
                            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
                            PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
                        }
                        else {
                            PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
                            PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14);
                        }
                    }
                }
                break;
        }
    }   
}