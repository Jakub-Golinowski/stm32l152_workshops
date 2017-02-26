 /*
 * Debug.cpp
 *
 *  Created on: 18.12.2016
 *      Author: jakub
 */

#include "Debug.hpp"

Debug::Debug() {
	// TODO Auto-generated constructor stub

}

Debug::~Debug() {
	// TODO Auto-generated destructor stub
}

void Debug::OutputClockOnPA8(OutputClock_t outputClock, OutputClockDivisor_t outputClockDivisor){

/*
 * Choose output Clock
 */
	RCC_MCOConfig(outputClock, outputClockDivisor);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);
/*
* PA8 pin configuration to be an MCO.
*/
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


   GPIO_InitTypeDef MCO_Pin;

   MCO_Pin.GPIO_Pin = GPIO_Pin_8;
   MCO_Pin.GPIO_Mode = GPIO_Mode_AF;
   MCO_Pin.GPIO_Speed = GPIO_Speed_40MHz;
   MCO_Pin.GPIO_PuPd = GPIO_PuPd_NOPULL;
   MCO_Pin.GPIO_OType = GPIO_OType_PP;

   GPIO_Init(GPIOA, &MCO_Pin);
}

