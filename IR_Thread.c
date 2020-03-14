
#include "IR_Thread.h"
#include "debug.h"
#include "LUT_ir.h"
#include "sensor_queue.h"
#include "timers.h"

void prvAutoReloadTimerCallback6( TimerHandle_t xTimer )
 {
    struct IR_Message message2;
    message2.val= 0x11;
    message2.tag = 0x33;
    bool sendStatus = SendMessageFromTimer(&message2);
 }

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void IR_Initialize ( void )

  Remarks:
    See prototype in ir.h.
 */

void IR_Initialize ( void )
{
    DRV_ADC_Open();
    DRV_ADC_Start();
}


/******************************************************************************
  Function:
    void IR_Tasks ( void )

  Remarks:
    See prototype in ir.h.
 */

void IR_Tasks ( void )
{
    TimerHandle_t xAutoReloadTimer6; 
    BaseType_t xTimer6Started;
    xAutoReloadTimer6 = xTimerCreate( 
            "AutoReload6", 
            pdMS_TO_TICKS(50),
            pdTRUE,
            (void *)ZERO, 
            prvAutoReloadTimerCallback6 );   
    xTimer6Started =  xTimerStart( xAutoReloadTimer6, ZERO ); 
    while(1){
        
        struct IR_Message message2;
        struct distance_Message th_message;
        bool IRstatus = ReceiveMessageIR(&message2);// top
        static uint8_t ir_data;
        switch(message2.tag)
        {
            case 0x11:
                ir_data = message2.val;
                break;
            case 0x33:
                //th_message.val = ir_data;
                th_message.val = lut_IR[ir_data];
                th_message.tag = 0x44;
                bool thread_send_status =  SendMessageFromUS(&th_message);
                break;
        }
    }
}
