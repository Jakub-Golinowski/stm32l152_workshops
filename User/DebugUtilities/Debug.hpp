/*
 * Debug.h
 *
 *  Created on: 18.12.2016
 *      Author: jakub
 */

#include "stm32l1xx_rcc.h"




#ifndef DEBUGUTILITIES_DEBUG_H_
#define DEBUGUTILITIES_DEBUG_H_

class Debug {
public:
	Debug();
	virtual ~Debug();

	enum OutputClock_t { NoClock, SYSCLK, HSI, MSI, HSE, PLLCLK, LSI, LSE };
	enum OutputClockDivisor_t { Div1, Div2 = 0x10, Div4 = 0x20 , Div8 = 0x30, Div16 = 0x40 };

	static void OutputClockOnPA8(OutputClock_t outputClock, OutputClockDivisor_t outputClockDivisor);
};

#endif /* DEBUGUTILITIES_DEBUG_H_ */
