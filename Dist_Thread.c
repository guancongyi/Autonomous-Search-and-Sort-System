#include "Dist_Thread.h"
#include "stdio.h"
#include "debug.h"
//#include "Distance.h"
#include "sensor_queue.h"
#include "timers.h"



void prvAutoReloadTimerCallback7( TimerHandle_t xTimerSending )
 { 
    struct distance_Message th_message;
    th_message.val = 100;
    th_message.tag = 0x66;
    bool sendStatus = SendMessageFromUS(&th_message);
 }

void Dist_Initialize ( void )
{
    PLIB_USART_ReceiverIdleStateLowEnable(USART_ID_5);
}


void Dist_Tasks ( void )
{
      
    TimerHandle_t xAutoReloadTimer7; 
    BaseType_t xTimer7Started;
    xAutoReloadTimer7 = xTimerCreate( 
            "AutoReload7", 
            pdMS_TO_TICKS(500),
            pdTRUE,
            (void *)ZERO, 
            prvAutoReloadTimerCallback7 );   
    xTimer7Started =  xTimerStart( xAutoReloadTimer7, ZERO ); 
    static uint8_t ultra_output;
    static uint8_t ir_output;
    uint8_t output = 0;
    int result = 0;
    while(1){
        
        distance_Message th_message;
        bool status = ReceiveMessageUS(&th_message);
        switch(th_message.tag)
        {
            case 0x22:
                ultra_output = th_message.val;
                break;
            case 0x44:
                ir_output = th_message.val;
                break;
            case 0x66:
                if (ultra_output == 5){
                    output = ir_output;
                }else{
                    output = ultra_output;
                }
//                if (output <= 100){
//                    result = 1;
//                }else{
//                    result = 0;
//                    //output = 0;
//                }
                sendRequest3(Sensor,0, 0, 0, 0, 20, 0, result,0,0,0);

                break;
        }
    }
    
}
