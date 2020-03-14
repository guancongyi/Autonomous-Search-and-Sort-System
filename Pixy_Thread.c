#include "Pixy_Thread.h"
#include "stdio.h"
#include "debug.h"
#include "pixy2.h"
#include "JSON.h"
#include "sensor_queue.h"
#include "timers.h"
#include "app.h"

#define TIMER_ISR 0
#define UART_ISR 1

void prvAutoReloadTimerCallback5( TimerHandle_t xTimer ) {
    Blocks signal;
    signal.tag = 0;

    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    BaseType_t status = Send_PIXY_Data_from_ISR(&signal, pxHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken);
}

void Pixy_Tasks( void ) {
    TimerHandle_t xAutoReloadTimer5; 
    BaseType_t xTimer1Started;
    xAutoReloadTimer5 = xTimerCreate( 
            "AutoReload5", 
            pdMS_TO_TICKS(100),
            pdTRUE,
            (void *)ZERO, 
            prvAutoReloadTimerCallback5 );   
    xTimer1Started =  xTimerStart( xAutoReloadTimer5, ZERO ); 
    
    // turn on lamp
//    Commands lampCmd;
//    strcpy(lampCmd.msg1, turnOnLamp);
//    BaseType_t status1 = Send_PIXY_Command_from_thread(&lampCmd);
//    SYS_INT_SourceEnable(INT_SOURCE_USART_3_TRANSMIT);
    
    while(1){
        /* parse data upon receiving */
        Blocks block1;
        BaseType_t receStatus = Recv_PIXY_Data_in_thread(&block1);
        Commands cmd;
        uint16_t x,width;
        int center, distance;

        BaseType_t status;
        switch(block1.tag){
            case TIMER_ISR: // from timer
                // send cmd
                cmd.sig = 'T';
                status = Send_PIXY_Command_from_thread(&cmd);
                if (!SYS_INT_SourceIsEnabled(INT_SOURCE_USART_3_TRANSMIT)) {
                    SYS_INT_SourceEnable(INT_SOURCE_USART_3_TRANSMIT);
                }
                //SYS_INT_SourceEnable(INT_SOURCE_USART_3_TRANSMIT);
                break;
            case UART_ISR: //from isr
                //debugPIXY(block1.data);
                x = getCenter(block1.data[CENTERX_UPPER_BYTE], block1.data[CENTERX_LOWER_BYTE]);
                width = getCenter(block1.data[OBJECT_WIDTH_UPPER_BYTE], block1.data[OBJECT_WIDTH_LOWER_BYTE]);
                distance = getDistance(width);
                center = isCenter(x,width);
                sendRequest3(Pixel,0, block1.data[SIGNATURE_BYTE], 0, 0, 0, 0,0,width, distance , center );
                break;
            default:
                break;
        }
    
    }
}
