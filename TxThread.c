#include "TxThread.h"
#include <stdio.h>
#include <math.h>
#include "sensor_queue.h"
#include "debug.h"
#include "JSON.h"
void Tx_Tasks_( void ) {
    BaseType_t check;
    static int MotorSequence, ArmSequence,PixelSequence,SensorSequence;
   
    while (1) {
        UNION_ message;
        check = ReceiveTransmit_Message(&message);
        
        dbgOutputLoc(0x38);
        if (check != pdTRUE) {
        }

        if (message.Mode == Motor) {
            cJSON * json = CreateJSON_Object();
            char str[20];
            addStringToJSON(json, "Sequence Number", itoa(str,MotorSequence,10));
            addStringToJSON(json, "Module name", "rover");
            if (message.operation == 0) {
                addStringToJSON(json, "Request type", "update");
            }
            else {
                addStringToJSON(json, "Request type", "getInfo");
            }
            
            if (message.Motor_Direction == 0) {
                addStringToJSON(json, "Direction", "Forward");
            }
            else if (message.Motor_Direction == 1) {
                addStringToJSON(json, "Direction", "Left");
            }
            else if (message.Motor_Direction == 2) {
                addStringToJSON(json, "Direction", "Right");
            }
            else  {
                addStringToJSON(json, "Direction", "Backward");
            }
            
            char str1[20];
            addStringToJSON(json, "Left Rover Speed", itoa(str1,message.Left_Motor_Speed,10));
            char str2[20];
            addStringToJSON(json, "Right Rover Speed", itoa(str2,message.Right_Motor_Speed,10));
            char str3[20];
            addStringToJSON(json, "Left Rover Remaining Distance", itoa(str3,message.Left_Motor_Distance,10));
            char str4[20];
            addStringToJSON(json, "Right Rover Remaining Distance", itoa(str4,message.Right_Motor_Distance,10));
            
            
            MotorSequence = MotorSequence + 1;
            sendRequest2(json);
        }
        else if (message.Mode == Arm) {
            cJSON * json = CreateJSON_Object();
            char str1[20];
            addStringToJSON(json, "Sequence Number", itoa(str1,ArmSequence,10));
            addStringToJSON(json, "Module name", "arm");
            if (message.operation == 0) {
                addStringToJSON(json, "Request type", "update");
            }
            else {
                addStringToJSON(json, "Request type", "getInfo");
            }
            if (message.arm_status == 0) {
                addStringToJSON(json, "Status", "Idle");
            }
            else {
                addStringToJSON(json, "Status", "Working");
            }
            
            char str2[20];
            addStringToJSON(json, "Item Count", itoa(str2,message.arm_item_count,10));
            ArmSequence = ArmSequence + 1;
            sendRequest2(json);
        }
        else if(message.Mode == Pixel) {
            /*
            cJSON * json = CreateJSON_Object();
            addNumberToJSON(json, "Sequence Number", PixelSequence);
            addStringToJSON(json, "Module name", "pixycam");
            if (message.operation == 0) {
                addStringToJSON(json, "Request type", "update");
            }
            else {
                addStringToJSON(json, "Request type", "getInfo");
            }
            if (message.Pixel_color == 1) {
                addStringToJSON(json, "Color", "Red");
            }
            else if(message.Pixel_color == 2) {
                addStringToJSON(json, "Color", "Green");
            }
            else if(message.Pixel_color == 3) {
                addStringToJSON(json, "Color", "Blue");
            }
            PixelSequence = PixelSequence + 1;
            sendRequest2(json);*/
            cJSON * json = CreateJSON_Object();
            char str1[20];
            addStringToJSON(json, "Sequence Number", itoa(str1,PixelSequence,10));
            //addNumberToJSON(json, "Distance to object", message.Sensor_distance);
            //addNumberToJSON(json, "Sequence Number", PixelSequence);
            addStringToJSON(json, "Module name", "pixycam");
            if (message.operation == 0) {
                addStringToJSON(json, "Request type", "update");
            }
            else {
                addStringToJSON(json, "Request type", "getInfo");
            }
            if (message.Pixel_color == 1) {
                addStringToJSON(json, "Color", "Red");
            }
            else if(message.Pixel_color == 2) {
                addStringToJSON(json, "Color", "Green");
            }
            else if(message.Pixel_color == 3) {
                addStringToJSON(json, "Color", "Blue");
            }
            else if(message.Pixel_color == 0) {
                addStringToJSON(json, "Color", "NONE");
            }
            char center[20];
            if(message.IsCenter == 1){
                addStringToJSON(json, "Center", itoa(center,message.IsCenter,10));
            }
            else if(message.IsCenter == 0){
                addStringToJSON(json, "Center", itoa(center,message.IsCenter,10));
            }
            char x[20];
            addStringToJSON(json, "Width", itoa(x,message.Pixel_x,10));
            char y[20];
            addStringToJSON(json, "Distance", itoa(y,message.Pixel_x,10));
            
            PixelSequence = PixelSequence + 1;
            sendRequest2(json);
        }
        else if (message.Mode == Sensor) {
            cJSON * json = CreateJSON_Object();
            char str1[20];
            addStringToJSON(json, "Sequence Number", itoa(str1,SensorSequence,10));
            //addNumberToJSON(json, "Sequence Number", SensorSequence);
            addStringToJSON(json, "Module name", "distsensor");
            if (message.operation == 0) {
                addStringToJSON(json, "Request type", "update");
            }
            else {
                addStringToJSON(json, "Request type", "getInfo");
            }
            char str2[20];
            //addNumberToJSON(json, "Distance to object", message.Sensor_distance);
            addStringToJSON(json, "Distance to object", itoa(str2,message.Sensor_distance,10));
//            if (message.Find_result == 0) {
//                addStringToJSON(json, "Find_result", "No object");
//            }
//            else if(message.Find_result == 1) {
//                addStringToJSON(json, "Find_result", "Found an object");
//            }
            
            SensorSequence = SensorSequence + 1;
            sendRequest2(json);
        }
    }
}
