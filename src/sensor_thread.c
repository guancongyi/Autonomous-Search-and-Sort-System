#include "sensor_thread.h"
#include "sensor_state.h"
#include <stdio.h>
#include <math.h>
#include "sensor_queue.h"
#include "debug.h"
#include "timers.h"
#include "app.h"
#include "JSON.h"
MotorStatus_ ReceiveMessage_() {
    BaseType_t check;
    //char flag = ' ';
    MotorStatus_ motor;
    dbgOutputLoc(SENSOR_THREAD_RECEIVE_MESSAGE_START);
    check = ReceiveSensor_ISR_Message(&motor); 
    dbgOutputLoc(SENSOR_THREAD_RECEIVE_MESSAGE_DONE);
    return motor;
}
void SendMessage(mode Mode,uint8_t Motor_Direction, uint8_t Left_Motor_Desired_Speed, 
                    uint8_t Right_Motor_Desired_Speed, int Left_Motor_Distance, 
                    int Right_Motor_Distance,uint8_t Color_Stuff, uint8_t Arm_Stuff  ) {
    BaseType_t check;
    TAG_UNION command;
    command.Mode = Mode;
    command.Motor_Direction = Motor_Direction;
    command.Left_Motor_Desired_Speed = Left_Motor_Desired_Speed;
    command.Right_Motor_Desired_Speed =  Right_Motor_Desired_Speed;
    command.Left_Motor_Distance = Left_Motor_Distance;
    command.Right_Motor_Distance = Right_Motor_Distance;
    command.Color_Stuff = Color_Stuff;
    command.Arm_Stuff = Arm_Stuff;
    dbgOutputLoc(SENSOR_THREAD_SEND_MESSAGE_START);
    check = SendMotorMessage(&command);
    dbgOutputLoc(SENSOR_THREAD_SEND_MESSAGE_DONE);
    if (check == pdFALSE) {
        dbgStopCode(MOTOR_MESSAGE_QUEUE_SEND_ERROR); 
    }
    portYIELD();
    //portEND_SWITCHING_ISR(pdTRUE);
}
void send_Valid_command() {
    
    static int count = 0;
    if (count == 0) {
        count = 20;
            //SendMessage(MOTOR, ZERO, LONG_DISTANCE_SPEED, LONG_DISTANCE_SPEED, LONG_DISTANCE, LONG_DISTANCE, ZERO,ZERO);
        sendRequest3(Motor,0,ZERO, LONG_DISTANCE_SPEED, LONG_DISTANCE_SPEED, LONG_DISTANCE,LONG_DISTANCE,0,0,0,0);
    }
    else if (count == 1) {
        count++;
        //SendMessage(MOTOR, 2, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE, NINETY_DEGREE, 0, 0);
        sendRequest3(Motor,0,2, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE,NINETY_DEGREE,0,0,0,0);
    }
    else if (count == 2) {
        count++;
        //SendMessage(MOTOR, 2, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE, NINETY_DEGREE, 0, 0);
        sendRequest3(Motor,0,2, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE,NINETY_DEGREE,0,0,0,0);
    }
    else if (count == 3) {
        count++;
        //SendMessage(MOTOR, 0, LONG_DISTANCE_SPEED, LONG_DISTANCE_SPEED, LONG_DISTANCE, LONG_DISTANCE, 0, 0);
        sendRequest3(Motor,0,ZERO, LONG_DISTANCE_SPEED, LONG_DISTANCE_SPEED, LONG_DISTANCE,LONG_DISTANCE,0,0,0,0);
    }
    else if (count == 4) {
        count++;
        //SendMessage(MOTOR, 1, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE, NINETY_DEGREE, 0, 0);
        sendRequest3(Motor,0,1, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE,NINETY_DEGREE,0,0,0,0);
    }
    else if (count == 5) {
        count++;
        //SendMessage(MOTOR, 1, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE / 2, NINETY_DEGREE / 2, 0, 0);
        sendRequest3(Motor,0,1, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE / 2,NINETY_DEGREE / 2,0,0,0,0);
    }
    else if (count == 6) {
        count++;
        //SendMessage(MOTOR, 0, SHORT_DISTANCE_SPEED, SHORT_DISTANCE_SPEED, SHORT_DISTANCE, SHORT_DISTANCE, 0, 0);
        sendRequest3(Motor,0,ZERO,SHORT_DISTANCE_SPEED, SHORT_DISTANCE_SPEED, SHORT_DISTANCE,SHORT_DISTANCE,0,0,0,0);
    }
    else if (count == 7) {
        count++;
        //SendMessage(MOTOR, 2, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE, NINETY_DEGREE, 0, 0);
        sendRequest3(Motor,0,2, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE,NINETY_DEGREE,0,0,0,0);
    }
    else if (count == 8) {
        count++;
        //SendMessage(MOTOR, 2, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE, NINETY_DEGREE, 0, 0);
        sendRequest3(Motor,0,2, ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE,NINETY_DEGREE,0,0,0,0);
    }
    else if (count == 9) {
        count++;
        //SendMessage(MOTOR, 0, SHORT_DISTANCE_SPEED, SHORT_DISTANCE_SPEED, SHORT_DISTANCE, SHORT_DISTANCE, 0, 0);
        sendRequest3(Motor,0,ZERO,SHORT_DISTANCE_SPEED, SHORT_DISTANCE_SPEED, SHORT_DISTANCE,SHORT_DISTANCE,0,0,0,0);
    }
    else if (count == 10) {
        count++;
        //SendMessage(MOTOR, 1, ROTATE_SPEED, ROTATE_SPEED,8 + NINETY_DEGREE / 2, 8 + NINETY_DEGREE / 2, 0, 0);
        sendRequest3(Motor,0,1,ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE / 2,NINETY_DEGREE / 2,0,0,0,0);
    }
    else if (count == 11) {
        count++;
        //SendMessage(MOTOR, 1, ROTATE_SPEED, ROTATE_SPEED, 8 + NINETY_DEGREE, 8 + NINETY_DEGREE, 0, 0);
        sendRequest3(Motor,0,1,ROTATE_SPEED, ROTATE_SPEED, NINETY_DEGREE,NINETY_DEGREE,0,0,0,0);
    }
}
void Sensor_Tasks ( void ) {
    
    dbgOutputLoc(ENTER_SENSOR_THREAD);
    dbgOutputLoc(SENSOR_THREAD_BEFORE_WHILE);
    /*
    while (1) {
        MotorStatus_ motor = ReceiveMessage_();
        //if (motor.left_distance > 0 || motor.right_distance > 0){
            //If the motor speed need adjustment (Accident happens, maybe motor is not in straight line)
            //sending MOTOR type command
            //Otherwise, send INVALIDATE command.
            //SendMessage(INVALIDATE, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
            //SendMessage(INVALIDATE, motor.direction ,motor.left_motor_current_speed, motor.right_motor_current_speed, motor.left_distance, motor.right_distance ,  ZERO, ZERO);
        //}
        //else {
            //send_Valid_command();
        //}
        if (motor.left_distance == 0 && motor.right_distance == 0) {
            send_Valid_command();
        }
    }*/
    
}