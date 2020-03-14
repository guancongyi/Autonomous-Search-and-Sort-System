#include "dummy_thread.h"
#include <stdio.h>
#include <math.h>
#include "sensor_queue.h"
#include "debug.h"
#include "timers.h"
#include "app.h"
void prvAutoReloadTimerCallback3( TimerHandle_t xTimer ) {
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    dbgOutputLoc(SW_ISR_SEND_DONE);
    BaseType_t success = SendDUMMY_MessageFromISR2("T", pxHigherPriorityTaskWoken);
    dbgOutputLoc(SW_ISR_SEND_START);
    if (success == pdFALSE) {
        dbgStopCode(DUMMY_THREAD_ERROR_3); 
    }
    portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken);
}

void Send_Wrong_Message2() {
    static int count;
    
    // Wrong message case 1: data length part is corrupted
    if (count == 0) {
        dbgUARTVal2("[001s1101ef97f18c676cfbbb041c77facc8b9161{\"Sequence\":46,\"From\":\"Motor\",\"To\":\"Motor\",\"Motor Direction\":\"Forward\",\"Left Rover Speed\":0,\"Right Rover Speed\":0,\"Left Rover Remaining Distance\":2292,\"Right Rover Remaining Distance\":2292}]");
    }
    // Wrong messsage case 2: the message is not ended by the value return from data length 
    else if(count == 1) {
        dbgUARTVal2("[0011011100ef97f18c676cfbbb041c77facc8b9161{\"Sequence\":46,\"From\":\"Motor\",\"To\":\"Motor\",\"Motor Direction\":\"Forward\",\"Left Rover Speed\":0,\"Right Rover Speed\":0,\"Left Rover Remaining Distance\":2292,\"Right Rover Rsaemaining Distance\":2292}]");
    }
    // Wrong message case 3: the hash part is corrupted
    else if(count == 2) {
        dbgUARTVal2("[0011011101ef97f1#676cfbbb041c77facc8b9161{\"Sequence\":46,\"From\":\"Motor\",\"To\":\"Motor\",\"Motor Direction\":\"Forward\",\"Left Rover Speed\":0,\"Right Rover Speed\":0,\"Left Rover Remaining Distance\":2292,\"Right Rover Remaining Distance\":2292}]");
    }
    // Wrong message case 4: Message is not ended as expected
    else if(count == 3) {
        dbgUARTVal2("[0011011101ef97f18c676cfbbb041c77facc8b9161{\"Sequence\":46,\"From\":\"Motor\",\"To\":\"Motor\",\"Motor Direction\":\"Forward\",\"Left Rover Speed\":0,\"Right Rover Speed\":0,\"Left Rover Remaining Distance\":2292,\"Right Rover Remaining Distance\":229#2}&]");
    }
    // Wrong message case 5: Message is ended as expected, but the md5 value of the json payload is not matched up with the sent hash value
    else if(count == 4) {
        dbgUARTVal2("[0011011101ef97f18c676cfbbb041c77facc8b9161{\"Sequence\":46,\"From\":\"Motor\",\"To\":\"Motor\",\"Motor Direction\":\"Forward\",\"Left Rover Speed\":0,\"Right Rover Speed\":0,\"Left Rover Remaining Distance\":322,\"Right Rover Remaining Distance\":2292}]");
    }
    // Wrong message cast 6:Stop byte didn't detect
    else if(count == 5) {
        dbgUARTVal2("[0011011101ef97f18c676cfbbb041c77facc8b9161{\"Sequence\":46,\"From\":\"Motor\",\"To\":\"Motor\",\"Motor Direction\":\"Forward\",\"Left Rover Speed\":0,\"Right Rover Speed\":0,\"Left Rover Remaining Distance\":2292,\"Right Rover Remaining Distance\":2292}");
        count = -1;
    }
    count++;
}
void Dummy_Tasks2( void ) {
    dbgOutputLoc(ENTER_DUMMY_THREAD);
    dbgOutputLoc(DUMMY_THREAD_BEFORE_WHILE);
    int count = 0;
    TimerHandle_t xAutoReloadTimer2; 
    BaseType_t xTimer1Started;
    xAutoReloadTimer2 = xTimerCreate( 
            "AutoReload2", 
            mainAUTO_RELOAD_TIMER_PERIOD
            ,pdTRUE,
            (void *)ZERO, 
            prvAutoReloadTimerCallback3 );   
    BaseType_t check;
    char command;
    xTimer1Started =  xTimerStart( xAutoReloadTimer2, ZERO ); 
    while (1) {
        dbgOutputLoc(DUMMY_THREAD_RECEIVE_START);
        check = ReceiveDUMMY_Message2(&command); 
        if (check == pdFALSE) {
            dbgStopCode(DUMMY_THREAD_ERROR_4); 
        }
        dbgOutputLoc(DUMMY_THREAD_RECEIVE_DONE);
        count++;
        if (count == 10) {
           // Send_Wrong_Message2();
            count = 0;
        }
        else {
            dbgUARTVal2("[0011011101ef97f18c676cfbbb041c77facc8b9161{\"Sequence\":46,\"From\":\"Motor\",\"To\":\"Motor\",\"Motor Direction\":\"Forward\",\"Left Rover Speed\":0,\"Right Rover Speed\":0,\"Left Rover Remaining Distance\":2292,\"Right Rover Remaining Distance\":2292}]");
        }
        
    }
}
