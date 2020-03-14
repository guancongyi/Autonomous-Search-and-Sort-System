/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "debug.h"


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
    void dbgOutputVal(unsigned int outVal) 

  @Summary
    The value of outVal must be <= 127. This routine must verify this.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void dbgOutputVal(unsigned int outVal) {   
    /*
    uint8_t maskVal_1 = outVal & 0b01111111;
    uint8_t portDMask = PORTD & 0b01111111;
    if (maskVal_1 != portDMask) {
        uint8_t MSB = PORTD & 0b10000000;
        MSB = MSB ^ 0b10000000;
        PORTD =  MSB | (uint8_t)outVal;
    } 
     */   
    //PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7);  
    uint8_t maskD_1;
    uint8_t maskD_2;
    uint8_t outVal_1;
    maskD_1 = PORTD ^ 0b10000000;
    maskD_2 = maskD_1 & 0b10000000;
    outVal_1 = (uint8_t)outVal & 0b01111111;
   // PORTD = maskD_2 | outVal_1 ;
 
}

/** 
  @Function
    void dbgUARTVal(unsigned char outVal) 

  @Summary
    This value will be written to the UART.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void dbgUARTVal(const char *str) {
   
  // UARTSendString("The average is: ");
 //  UARTSendString(str);
 //  UARTSendString(" centimeters");
 //  UARTSendString("\r\n");
}

/** 
  @Function
    dbgOutputLoc(unsigned int outVal)

  @Summary
    The value of outVal must be <= 127. This routine must verify this.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void dbgOutputLoc(unsigned int outVal) {
    uint8_t maskE_1;
    uint8_t maskE_2;
    uint8_t outVal_1;
    maskE_1 = PORTE ^ 0b10000000;
    maskE_2 = maskE_1 & 0b10000000;
    outVal_1 = (uint8_t)outVal & 0b01111111;
    PORTE = maskE_2 | outVal_1 ;

}

/** 
  @Function
    dbgStopCode(unsigned int outVal)

  @Summary
    This debug routine is called when all code stop. It will also output an unique value if that happens

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void dbgStopCode(uint8_t Case ) {
    DRV_ADC_Stop();
    DRV_ADC_Close();
    DRV_OC0_Stop();
    DRV_OC0_Disable();
    DRV_OC1_Stop();
    DRV_OC1_Disable();
    DRV_TMR0_Stop();
    DRV_TMR1_Stop();
    DRV_TMR2_Stop();
    DRV_USART_Deinitialize(DRV_USART_INDEX_0);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);  
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
    PORTE = Case;
    while (1) {
        dbgUARTVal("!!");
        vTaskDelay(100);
        
    }
}


/* *****************************************************************************
 End of File
 */