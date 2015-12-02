/*
 * UART3_messages_control.h
 *
 *  Created on: 11 lis 2015
 *      Author:  Paulina Sadowska
 */

#ifndef UART3_MESSAGES_CONTROL_H_
#define UART3_MESSAGES_CONTROL_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/uart.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

/** macros of data recieved from uart **/

//special characters
#define START_BYTE '{'
#define STOP_BYTE '}'
#define ROBOT_STOP_SIGN 'S'
#define ROBOT_MOVE_SIGN 'M'

//indexes on in message for informations
//in message
#define INDEX_ROBOT_STOP_SIGN 1
#define INDEX_ANGLE 2
#define INDEX_VELOCITY  5
//out message
#define INDEX_START_BYTE 0
#define INDEX_CURRENT_1  1
#define INDEX_CURRENT_2  5
#define INDEX_STOP_BYTE  9


 //length of the message
#define MESSAGE_LENGTH_IN 9 //maximum input message length (contains velocity and angle)
#define MESSAGE_LENGTH_OUT 10 //output message length

extern unsigned char inBuffer[MESSAGE_LENGTH_IN]; //buffor to store readed message
extern unsigned char outBuffer[MESSAGE_LENGTH_OUT]; //buffor to store readed message
extern unsigned int i; //variable to manage char position in inBuffer array
extern bool MessageInProgress;

extern bool moveRobotFlag;
extern uint16_t drivingAngle;
extern uint32_t velocity;
extern bool UARTDataChanged;

//EventHandler
void(*UartDataChangedEventHandler)(void);

//gets character and create incoming void WriteCharToBuffer(unsigned char character);message in inBuffer
void WriteCharToBuffer(unsigned char character);
void DecodeMessage();
void CodeMessage();
void SendMessage();
void OnUartDataChangedEvent();
void UARTDataChangedSubscribe(void(*uartDataChangedEventHandler)(void));

#endif /* UART3_MESSAGES_CONTROL_H_ */
