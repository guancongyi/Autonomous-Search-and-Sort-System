#include "RxThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sensor_queue.h"
#include "debug.h"
#include "JSON.h"
#include "system_config.h"
#include "system_definitions.h"
#include <ctype.h>
typedef enum {Idle,Length,Hash,Json,Checking} state;

void Rx_Tasks_( void ) {
    dbgOutputLoc(ENTER_TX_THREAD);
    dbgOutputLoc(TX_THREAD_BEFORE_WHILE);
    BaseType_t check = pdTRUE;
    //char data[1024] = "[0011011101ef97f18c676cfbbb041c77facc8b9161{\"Sequence\":46,\"From\":\"Motor\",\"To\":\"Motor\",\"Motor Direction\":\"Forward\",\"Left Rover Speed\":0,\"Right Rover Speed\":0,\"Left Rover Remaining Distance\":2292,\"Right Rover Remaining Distance\":2292}]";
    char data[1024];
    state state_ = Idle;
    int i = 0;
    char len[10];
    char hash[33];
    char json[512];
    int data_size;
    int count;
    int WrongMSG = 0;
    int CorrectMSG = 0;
    int MotorSequence = 0;
    int PixySequence = 0;
    while (1) {
        //Receive the message from the ReceiveMSG Queue
        // MQ_recv_in_thread(&b);
        //memset(data, 0, sizeof(data));
        ReceiveUART_RX_Message(data);
        for (i = 0; i < strlen(data); i++) {
            if (state_ == Idle) {
                if (data[i] == '[') {
                    state_ = Length;
                    data_size = 0;
                    count = 0;
                    memset(len, 0, sizeof(len));
                    memset(hash, 0, sizeof(hash));
                    memset(json, 0, sizeof(json));
                }
            }
            else if(state_ == Length) {
                if ((data[i] != '0' && data[i] != '1') || count > 10) {
                    state_  = Idle;
                    WrongMSG = WrongMSG + 1;
                    data_size = 0;
                    count = 0;
                    memset(len, 0, sizeof(len));
                    memset(hash, 0, sizeof(hash));
                    memset(json, 0, sizeof(json));
                }
                else {
                    len[count] = data[i];
                    count = count + 1;
                    if (count == 10) {
                        int k = 0;
                        int val = 512;
                        for (k = 0; k < strlen(len); k++) {
                            if (len[k] == '1') {
                                data_size = data_size + val;
                            }
                            val = val / 2;
                         }
                        count = 0;
                        memset(len, 0, sizeof(len));
                        memset(hash, 0, sizeof(hash));
                        memset(json, 0, sizeof(json));
//                        state_ = Hash;
                        state_ = Json;
                    }
                }
            }
//            else if(state_ == Hash) {
//                if ((isdigit(data[i]) == 0 && isalpha(data[i]) == 0) || count > 32 || data_size <= 0) {
//                    state_  = Idle;
//                    WrongMSG = WrongMSG + 1;
//                    data_size = 0;
//                    count = 0;
//                    memset(len, 0, sizeof(len));
//                    memset(hash, 0, sizeof(hash));
//                    memset(json, 0, sizeof(json));
//                }
//                else {
//                    data_size = data_size - 1;
//                    hash[count] = data[i];
//                    count = count + 1;
//                    if (count == 32) {
//                        state_ = Json;
//                        count = 0;
//                        memset(json, 0, sizeof(json));
//                    }
//                }
//            }
            else if(state_ == Json) {
                if(data_size <= 0) {
                    state_  = Idle;
                    WrongMSG = WrongMSG + 1;
                    data_size = 0;
                    count = 0;
                    memset(len, 0, sizeof(len));
                    memset(hash, 0, sizeof(hash));
                    memset(json, 0, sizeof(json));
                }
                else {
                    json[count] = data[i];
                    count = count + 1;
                    data_size = data_size - 1;
                    if (data_size == 0) {
                        state_ = Checking;
                        count = 0;
                    }
                }
            
            }
            else if (state_ == Checking) {
                
                if (data[i] != ']') {
                    state_  = Idle;
                    WrongMSG = WrongMSG + 1;
                    data_size = 0;
                    count = 0;
                    memset(len, 0, sizeof(len));
                    memset(hash, 0, sizeof(hash));
                    memset(json, 0, sizeof(json));
                }
                else {
                    
//                    unsigned char result[16];
//                    MD5(json, result);
//                    char converted[33];
//                    int k =0;
//                    for (k=0;k<16;k<k++){
//                        sprintf(&converted[k*2], "%02x", result[k]);
//                    }
//                    if (strlen(hash) == 32 && strlen(converted) == 32) {
//                        int check = 0;
//                        for (k = 0; k < strlen(hash); k++) {
//                            if (hash[k] != converted[k]) {
//                                check = 1;
//                            }
//                        }
//                        if (check == 1) {
//                            WrongMSG = WrongMSG + 1;
//                        }
                        //else {
                            CorrectMSG = CorrectMSG + 1;
                            cJSON * json_ = parsing(json);
                            char *Module_name = getStringTypeObject(json_, "Module name");
                            if (strcmp(Module_name, "pixycam") == 0) {
                                cJSON * information = cJSON_GetObjectItem(json_, "Informations");
                                TAG_UNION command;
                                command.Mode = LOCATE;
                                if (atoi(getStringTypeObject(information, "Sequence Number")) != PixySequence) {
                                    PixySequence = atoi(getStringTypeObject(information, "Sequence Number"));
                                    command.Color_Stuff = atoi(getStringTypeObject(information, "Center"));
                                    //if (command.Color_Stuff == 1) {
                                    SendMotorMessage(&command);
                                    //}
                                }
                                deleteJSON(information);
                            }
                            else if ( strcmp(Module_name,"distsensor") == 0) {
                                cJSON * information = cJSON_GetObjectItem(json_, "Informations");
                                TAG_UNION command;
                                command.Left_Motor_Encoder = 0;
                                command.Right_Motor_Encoder = 0;
                                command.Left_Motor_Distance = atoi(getStringTypeObject(information, "Distance to object")) * 76.4;
                                command.Right_Motor_Distance = atoi(getStringTypeObject(information, "Distance to object")) * 75.4;
                                if (atoi(getStringTypeObject(information, "Sequence Number")) != MotorSequence) {
                                    MotorSequence = atoi(getStringTypeObject(information, "Sequence Number"));
                                    if (command.Left_Motor_Distance > 0 && command.Right_Motor_Distance > 0) {
//                                        PLIB_PORTS_PinDirectionOutputSet(PORPLIBTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
//                                        PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
                                        command.Motor_Direction = 0;
                                        command.Sequence_Num = atoi(getStringTypeObject(information, "Sequence Number"));
                                        command.Left_Motor_Desired_Speed = LONG_DISTANCE_SPEED;
                                        command.Right_Motor_Desired_Speed = LONG_DISTANCE_SPEED;
                                        command.Mode = MOTOR;
                                        SendMotorMessage(&command);
                                        //deleteJSON(information);
                                    }
                                    else if (command.Left_Motor_Distance == 0 && command.Right_Motor_Distance == 0) {
//                                        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
//                                        PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
                                        command.Left_Motor_Distance = NINETY_DEGREE * 2;
                                        command.Right_Motor_Distance = NINETY_DEGREE * 2;
                                        command.Motor_Direction = 2;
                                        command.Sequence_Num = atoi(getStringTypeObject(information, "Sequence Number"));
                                        command.Left_Motor_Desired_Speed = ROTATE_SPEED;
                                        command.Right_Motor_Desired_Speed = ROTATE_SPEED;
                                        command.Mode = MOTOR;
                                        SendMotorMessage(&command);
                                        //deleteJSON(information);
                                    }        
                                }
                                deleteJSON(information);
                            }
                            vPortFree(Module_name);
                            deleteJSON(json_);
                        //}
                        state_  = Idle;
                        data_size = 0;
                        count = 0;
                        memset(len, 0, sizeof(len));
                        memset(hash, 0, sizeof(hash));
                        memset(json, 0, sizeof(json));
                    
                    //}
//                    else {
//                        WrongMSG = WrongMSG + 1;
//                        state_  = Idle;
//                        data_size = 0;
//                        count = 0;
//                        memset(len, 0, sizeof(len));
//                        memset(hash, 0, sizeof(hash));
//                        memset(json, 0, sizeof(json));
//                    }
                }
        }
    }
        
    }
}