
#ifndef DEBUG_H
#include <stdbool.h>
#include "app.h"




    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.

      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
     */
#define ENTERING_TASK 0x00    
#define BEFORE_WHILE 0x01
#define ENTERING_ISR 0x10
#define LEAVING_ISR 0x11

#define ISR_SEND_MESSAGE_TO_QUEUE_START 0x12
#define ISR_SEND_MESSAGE_TO_QUEUE_DONE 0x13

#define MOTOR_TASK_RECEIVE_FROM_QUEUE_START 0x02
#define MOTOR_TASK_RECEIVE_FROM_QUEUE_DONE 0x03
#define MOTOR_TASK_SEND_SW_ISR_START 0x04
#define MOTOR_TASK_SEND_SW_ISR_DONE 0x05

#define ENTER_SENSOR_THREAD 0x30
#define SENSOR_THREAD_BEFORE_WHILE 0x31
#define SENSOR_THREAD_SEND_MESSAGE_START 0x32
#define SENSOR_THREAD_SEND_MESSAGE_DONE 0x33
#define SENSOR_THREAD_RECEIVE_MESSAGE_START 0x34
#define SENSOR_THREAD_RECEIVE_MESSAGE_DONE 0x35

#define SW_ISR_ENTER 0x40
#define SW_ISR_RECEIVE_FROM_QUEUE_START 0x41
#define SW_ISR_RECEIVE_FROM_QUEUE_DONE 0x42
#define SW_ISR_SEND_START 0x43
#define SW_ISR_SEND_DONE 0x44
#define SW_ISR_LEAVE 0x45

#define MOTOR_MESSAGE_QUEUE_SEND_ERROR 0x50
#define MOTOR_MESSAGE_QUEUE_RECEIVE_ERROR 0x51
#define MOTOR_MESSAGE_SEND_SW_ISR_ERROR 0x52
#define SENSOR_QUEUE_RECEIVE_ERROR 0x53
#define SW_ISR_SEND_ERROR 0x65
#define DUMMY_THREAD_ERROR 0x66
#define DUMMY_THREAD_ERROR_2 0x67
#define DUMMY_THREAD_ERROR_3 0x68
#define DUMMY_THREAD_ERROR_4 0x69

#define TX_THREAD_ERROR 0x60

#define ENTER_DUMMY_THREAD 0x54
#define DUMMY_THREAD_BEFORE_WHILE 0x55
#define DUMMY_THREAD_RECEIVE_START 0x56
#define DUMMY_THREAD_RECEIVE_DONE 0x57

#define SEND_MESSAGE_TO_TX_THREAD 0x58
#define SEND_MESSAGE_TO_TX_THREAD_DONE 0x59

#define ENTER_TX_THREAD 0x61
#define TX_THREAD_BEFORE_WHILE 0x62
#define TX_THREAD_RECEIVE_START 0x63
#define TX_THREAD_RECEIVE_END 0x64
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    /** 
    @Function
      void dbgOutputVal(unsigned int outVal) 

    @Summary
      The value of outVal must be <= 127. This routine must verify this.

    @Remarks
      Refer to the example_file.h interface header for function usage details.
   */
    void dbgOutputVal(unsigned int outVal);
    
    /** 
    @Function
      void dbgUARTVal(unsigned char outVal) 

    @Summary
      This value will be written to the UART.

    @Remarks
      Refer to the example_file.h interface header for function usage details.
   */
    void dbgUARTVal(const char *str);
    
    /** 
    @Function
      dbgOutputLoc(unsigned int outVal)

    @Summary
      The value of outVal must be <= 127. This routine must verify this.

    @Remarks
      Refer to the example_file.h interface header for function usage details.
   */
    void dbgOutputLoc(unsigned int outVal);

    /** 
    @Function
      dbgStopCode(unsigned int outVal)

    @Summary
      This debug routine is called when all code stop. It will also output an unique value if that happens

    @Remarks
      Refer to the example_file.h interface header for function usage details.
   */
    void dbgStopCode(uint8_t Case); 
#endif


