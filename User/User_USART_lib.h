/*
 * User_USART_lib.h
 *
 *  Created on: 09.03.2017
 *      Author: piter
 */

#ifndef USER_USART_LIB_H_
#define USER_USART_LIB_H_

#include "stm32l1xx.h"

#define UART_RX_BUF_SIZE 32 // USART receiving buffer, should be a power of 2 (f.e. 2^5 = 32)
#define UART_RX_BUF_MASK (UART_RX_BUF_SIZE-1) //USART receiving buffer mask, to control buffer head and tail indexes
#define DELIMETER 13 // A symbol that ends the message

volatile uint8_t uart_rx_buffer[UART_RX_BUF_SIZE];
volatile uint8_t uart_rx_buffer_tail_index;
volatile uint8_t uart_rx_buffer_head_index;

volatile uint8_t uart_received_message_flag;

int8_t uart_getByte(uint8_t * receivedData);  // Puts a byte from the uart_rx_buffer to receivedData address
int8_t uart_getMessage(uint8_t * message);	  // Puts all new received data to message address

void init_UART2();							 // UART2 initialization, with RX interrupt init

#endif /* USER_USART_LIB_H_ */
