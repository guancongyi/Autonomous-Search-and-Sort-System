/* ************************************************************************** */
/** 

  @File Name
    sensor_queue.c

  @Summary
 * Include the basic functionality of FreeRTOS message queue

 */
#include "sensor_queue.h"

//This function will create a message queue 
//@param QUEUE_LENGTH The number of unit that can be stored in the queue
//@param QUEUE_ITEM_SIZE The size of the unit in byte
QueueHandle_t createMessageQ() {
    return xQueueCreate( QUEUE_LENGTH, QUEUE_ITEM_SIZE ); 
}
QueueHandle_t creatUARTMSQ() {
    return xQueueCreate(10, sizeof(char)); 
}
QueueHandle_t creatMOTOR_Queue() {
    return xQueueCreate(MOTOR_QUEUE_LENGTH,MOTOR_QUEUE_ITEM_SIZE); 
}
QueueHandle_t createMOTOR_ISR_Queue() {
    return xQueueCreate(MOTOR_QUEUE_LENGTH,MOTOR_ISR_ITEM_SIZE); 
}
QueueHandle_t createSENSOR_ISR_Queue() {
    return xQueueCreate(QUEUE_LENGTH,MOTOR_ISR_ITEM_SIZE); 
}
QueueHandle_t createBreak_Queue() {
    return xQueueCreate(QUEUE_LENGTH,SIGNAL_SIZE); 
}

QueueHandle_t createUART_TRANSMIT_Queue() {
    return xQueueCreate(40,300); 
}

QueueHandle_t createDUMMY_Queue() {
    return xQueueCreate(QUEUE_LENGTH,SIGNAL_SIZE); 
}

QueueHandle_t createDUMMY_Queue2() {
    return xQueueCreate(QUEUE_LENGTH,SIGNAL_SIZE); 
}

QueueHandle_t createTransmit_Queue() {
    return xQueueCreate(UNION_LENGTH,UNION_SIZE); 
}

QueueHandle_t create_MQ_uart_thread() {
    return xQueueCreate( UART_THREAD_Q_LENGTH, UART_THREAD_Q_SIZE ); 
}

QueueHandle_t create_MQ_ISR() {
    return xQueueCreate( ISR_Q_LENGTH, ISR_Q_SIZE ); 
}

QueueHandle_t create_UART_RX() {
    return xQueueCreate(10, 1024); 
}

//This function will send data to the message queue
//@param pvItemToQueue The unit we send to the queue
//@param pxHigherPriorityTaskWoken Check if any task is woken when the data is send to the queue
BaseType_t SendMessageFromISR(const void *pvItemToQueue,  BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendFromISR(xQueue, pvItemToQueue, &pxHigherPriorityTaskWoken);
}

BaseType_t SendUARTMessageFromISR(char *pvItemToQueue, BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendFromISR(UART_Queue, pvItemToQueue, &pxHigherPriorityTaskWoken);
}

BaseType_t SendMotorMessage(const void *pvItemToQueue) {
    return xQueueSend(MOTOR_Queue, pvItemToQueue, portMAX_DELAY );
}

BaseType_t SendMotorMessageFromISR(const void *pvItemToQueue, BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendFromISR(MOTOR_Queue, pvItemToQueue, &pxHigherPriorityTaskWoken);
}

BaseType_t SendMotor_ISR_Message(const void *pvItemToQueue) {
    return xQueueSend(MOTOR_ISR_Queue, pvItemToQueue, portMAX_DELAY );
}

BaseType_t SendSensor_ISR_MessageFromISR(const void *pvItemToQueue, BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendFromISR(SENSOR_ISR_Queue, pvItemToQueue, &pxHigherPriorityTaskWoken);
}   

BaseType_t SendBreak_MessageFromISR(const void *pvItemToQueue, BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendFromISR(BREAK_Queue, pvItemToQueue, &pxHigherPriorityTaskWoken);
}

BaseType_t SendUART_TRANSMIT_Message(const void *pvItemToQueue) {
    return xQueueSend(UART_TRANSMIT_Queue, pvItemToQueue, portMAX_DELAY );
}

BaseType_t SendDUMMY_MessageFromISR(const void *pvItemToQueue, BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendFromISR(DUMMY_Queue, pvItemToQueue, &pxHigherPriorityTaskWoken);
}

BaseType_t SendDUMMY_MessageFromISR2(const void *pvItemToQueue, BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendFromISR(DUMMY_Queue2, pvItemToQueue, &pxHigherPriorityTaskWoken);
}

BaseType_t SendTransmit_Message(const void *pvItemToQueue) {
    return xQueueSend(TRANSMIT_Queue, pvItemToQueue, portMAX_DELAY );
}

BaseType_t MQ_send_from_ISR(const void *pvItemToQueue,  BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendToBackFromISR(uart_thread_Q_handle, pvItemToQueue, &pxHigherPriorityTaskWoken);
}

BaseType_t MQ_send_from_callback(const void *pvItemToQueue){
    return xQueueSendToBack(ISR_Q_handle, pvItemToQueue, portMAX_DELAY );
}

BaseType_t Send_from_UART_RX_ISR(const void *pvItemToQueue,  BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueSendFromISR(UART_RX_Queue, pvItemToQueue, &pxHigherPriorityTaskWoken);
}
//This function will receive data from the message queue
//@param message The data received
BaseType_t ReceiveMessage(AMessage *message) {
    return xQueueReceive( xQueue, message, portMAX_DELAY );
}

BaseType_t ReceiveUARTMessage(char *message) {
    return xQueueReceive(UART_Queue, message, portMAX_DELAY );
}

BaseType_t ReceiveMotorMessage(TAG_UNION *message) {
    return xQueueReceive(MOTOR_Queue, message, portMAX_DELAY );
}

BaseType_t ReceiveMotor_ISR_Message(MotorStatus_ *message,BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueReceiveFromISR(MOTOR_ISR_Queue, message,&pxHigherPriorityTaskWoken);
}
BaseType_t ReceiveSensor_ISR_Message(MotorStatus_ *message) {
    return xQueueReceive(SENSOR_ISR_Queue, message,  portMAX_DELAY);
}
BaseType_t ReceiveBreak_Message(char *message) {
    return xQueueReceive(BREAK_Queue, message, portMAX_DELAY );
}
BaseType_t ReceiveUART_TRANSMIT_Message(char *message,BaseType_t pxHigherPriorityTaskWoken) {
    return xQueueReceiveFromISR(UART_TRANSMIT_Queue, message,&pxHigherPriorityTaskWoken);
}

BaseType_t ReceiveDUMMY_Message(char *message) {
    return xQueueReceive(DUMMY_Queue, message, portMAX_DELAY );
}

BaseType_t ReceiveDUMMY_Message2(char *message) {
    return xQueueReceive(DUMMY_Queue2, message, portMAX_DELAY );
}

BaseType_t ReceiveTransmit_Message(UNION_ *message) {
    return xQueueReceive(TRANSMIT_Queue, message, portMAX_DELAY );
}
BaseType_t ReceiveUART_RX_Message(char *message) {
    return xQueueReceive(UART_RX_Queue, message, portMAX_DELAY );
}

//#######PIXY
QueueHandle_t create_PIXY_Command_Q() {

    return xQueueCreate( PIXY_COMMAND_Q_LENGTH, PIXY_COMMAND_Q_SIZE ); 

}

BaseType_t Send_PIXY_Command_from_thread(const void *pvItemToQueue){

    return xQueueSendToBack(PIXY_Command_Q_handle, pvItemToQueue, portMAX_DELAY );

}

BaseType_t Recv_PIXY_Command_in_ISR(Commands *message, BaseType_t TaskWokenByReceive){

    return xQueueReceiveFromISR( PIXY_Command_Q_handle, message, &TaskWokenByReceive);

}

QueueHandle_t create_PIXY_Data_Q() {

    return xQueueCreate( PIXY_Data_Q_LENGTH, PIXY_Data_Q_SIZE ); 

}

BaseType_t Send_PIXY_Data_from_ISR(const void *pvItemToQueue,  BaseType_t pxHigherPriorityTaskWoken) {

    return xQueueSendFromISR(PIXY_Data_Q_handle, pvItemToQueue, &pxHigherPriorityTaskWoken);

}

BaseType_t Recv_PIXY_Data_in_thread(Blocks *b) {

    return xQueueReceive( PIXY_Data_Q_handle, b, portMAX_DELAY );

}


//###################DISTANCE

QueueHandle_t createMessageQIR() {
    return xQueueCreate( IR_QUEUE_LENGTH, IR_QUEUE_ITEM_SIZE ); 
}
QueueHandle_t createMessageQISR() {
    return xQueueCreate( Thread_ISR_QUEUE_LENGTH, Thread_ISR_QUEUE_ITEM_SIZE ); 
}
QueueHandle_t createMessageQThread() {
    return xQueueCreate( TH_QUEUE_LENGTH, TH_QUEUE_ITEM_SIZE ); 
}
QueueHandle_t US_createMessageQ() {
    return xQueueCreate( US_QUEUE_LENGTH, US_QUEUE_ITEM_SIZE ); 
}



bool SendMessageFromTimer(const void *pvItemToQueue){
    BaseType_t Timer_Queue_Send_Status;
    Timer_Queue_Send_Status = xQueueSendToBack(xQueue2, pvItemToQueue, portMAX_DELAY);
    if (Timer_Queue_Send_Status == pdTRUE){
        return true;
    }
    else{
        return false;
    } 
}

bool SendMessageFromADCISR(const void *pvItemToQueue,  BaseType_t *pxHigherPriorityTaskWoken){ 
    
    BaseType_t ADC_Queue_Send_Status;
    ADC_Queue_Send_Status = xQueueSendFromISR(xQueue2, pvItemToQueue, pxHigherPriorityTaskWoken);
    if (ADC_Queue_Send_Status == pdTRUE){
        return true;
    }
    else{
        return false;
    }   
}



bool ReceiveMessageIR(IR_Message *message) {
    BaseType_t Queue_Receive_Status;
    Queue_Receive_Status = xQueueReceive( xQueue2, message, portMAX_DELAY );
    if (Queue_Receive_Status == pdPASS){
        return true;
    }
    else{
        return false;
    }       
}

bool SendMessageFromThread(const void *pvItemToQueue){
    BaseType_t TH_Queue_Send_Status;
    TH_Queue_Send_Status = xQueueSendToBack(xQueueISR, pvItemToQueue, portMAX_DELAY);
    if (TH_Queue_Send_Status == pdTRUE){
        return true;
    }
    else{
        return false;
    }         
}

bool ReceiveMessageISR(Thread_Mss *message, BaseType_t pxHigherPriorityTaskWoken) {
    BaseType_t ISR_Queue_Receive_Status;
    ISR_Queue_Receive_Status = xQueueReceiveFromISR(xQueueISR, message, &pxHigherPriorityTaskWoken);
    if ( ISR_Queue_Receive_Status == pdTRUE){
        return true;
    }
    else{
        return false;
    }       
}

bool SendMessageFromUS(const void *pvItemToQueue) {
    BaseType_t TH_Queue_Send_Status;
    TH_Queue_Send_Status = xQueueSendToBack(xQueueTh, pvItemToQueue, (portMAX_DELAY));
    if (TH_Queue_Send_Status == pdTRUE){
        return true;
    }
    else{
        return false;
    }       
}

bool ReceiveMessageUS(distance_Message *message) {
    BaseType_t Queue_Receive_Status;
    Queue_Receive_Status = xQueueReceive( xQueueTh, message, portMAX_DELAY );
    if (Queue_Receive_Status == pdPASS){
        return true;
    }
    else{
        return false;
    }       
}

bool US_SendMessageFromISR(const void *pvItemToQueue,  BaseType_t *pxHigherPriorityTaskWoken) {
    BaseType_t ISR_Queue_Send_Status;
    ISR_Queue_Send_Status = xQueueSendFromISR(US_xQueue, pvItemToQueue, pxHigherPriorityTaskWoken);
    if (ISR_Queue_Send_Status == pdTRUE){
        return true;
    }
    else{
        return false;
    }       
}

bool US_ReceiveMessage(US_Message *message) {
    BaseType_t Queue_Receive_Status;
    Queue_Receive_Status = xQueueReceive( US_xQueue, message, portMAX_DELAY );
    if (Queue_Receive_Status == pdPASS){
        return true;
    }
    else{
        return false;
    }       
}