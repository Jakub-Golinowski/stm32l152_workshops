/*
 * User_USART_lib.c
 *
 *  Created on: 09.03.2017
 *      Author: piter
 */


#include "User_USART_lib.h"



int8_t uart_getByte(uint8_t * receivedData) {
	if(uart_rx_buffer_head_index == uart_rx_buffer_tail_index)
		return 0; //Return error code when the buffer is empty

	uart_rx_buffer_tail_index = (uart_rx_buffer_tail_index+1) & UART_RX_BUF_MASK; //Increment tail index and & with mask, so it never exceeds the buffer size - 1

	*receivedData = uart_rx_buffer[uart_rx_buffer_tail_index];		//Insert byte from Data Register to circular buffer

	return 1;
}


int8_t uart_getMessage(uint8_t * message){
	uint8_t counter = 0;
	while(uart_getByte(message+counter)){			// read bytes from uart_rx_buffer until it returns error code which means that it's empty
		counter++;
	}
	return 1;
}

void USART2_IRQHandler() {

	if ( USART_GetITStatus(USART2, USART_IT_RXNE)){
		uint8_t data;
		uint8_t tmp_head;
		data = USART2->DR;
		tmp_head = (uart_rx_buffer_head_index+1) & UART_RX_BUF_MASK;
		if(data == DELIMETER || tmp_head == uart_rx_buffer_tail_index )		// If the circular buffer is full (head caught up to tail) or received char is a DELIMETER,
			uart_received_message_flag = 1;								    // set the flag and stop writing new data to buffer
		else
		{
			uart_rx_buffer_head_index = tmp_head;
			uart_rx_buffer[uart_rx_buffer_head_index] = data;
		}
		USART_ClearFlag(USART2, USART_IT_RXNE);

	}

}

void init_UART2(){
	  //GPIO configuration

	  GPIO_InitTypeDef UART2Pins_InitStruct;

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2 );
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2 );

	  UART2Pins_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	  UART2Pins_InitStruct.GPIO_OType = GPIO_OType_PP;
	  UART2Pins_InitStruct.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3;
	  UART2Pins_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	  //UART2Pins_InitStruct.GPIO_Speed = GPIO_Speed_400KHz;
	  GPIO_Init(GPIOA,&UART2Pins_InitStruct);

	  //UART peripheral configuration

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	  USART_InitTypeDef UART2_InitStruct;

	  UART2_InitStruct.USART_BaudRate = 115200;
	  UART2_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  UART2_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	  UART2_InitStruct.USART_Parity = USART_Parity_No;
	  UART2_InitStruct.USART_StopBits = USART_StopBits_1;
	  UART2_InitStruct.USART_WordLength = USART_WordLength_8b;
	  USART_Init(USART2, &UART2_InitStruct);

	  USART_Cmd(USART2,ENABLE);

	  // USART 2 RX interrupt configuration
	  NVIC_InitTypeDef NVIC_InitStructure;

	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
}
