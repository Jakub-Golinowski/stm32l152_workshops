/*
******************************************************************************
File:     main.cpp
Info:     Generated by Atollic TrueSTUDIO(R) 7.0.0   2016-12-18

The MIT License (MIT)
Copyright (c) 2009-2016 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************
*/

/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"

#include "DebugUtilities/Debug.hpp"


/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void send_char_UART2(char c)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
}

void send_string_UART2(char const *s)
{
	while (*s)
	send_char_UART2(*s++);
}

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  /**
  *  IMPORTANT NOTE!
  *  See the <system_*.c> file and how/if the SystemInit() function updates 
  *  SCB->VTOR register. Sometimes the symbol VECT_TAB_SRAM needs to be defined 
  *  when building the project if code has been located to RAM and interrupts 
  *  are used. Otherwise the interrupt table located in flash will be used.
  *  E.g.  SCB->VTOR = 0x20000000;  
  */

  /**
  *  At this stage the microcontroller clock setting is already configured,
  *  this is done through SystemInit() function which is called from startup
  *  file (startup_stm32l1xx_hd.s) before to branch to application main.
  *  To reconfigure the default setting of SystemInit() function, refer to
  *  system_stm32l1xx.c file
  */

  /* TODO - Add your application code here */
  Debug::OutputClockOnPA8(Debug::NoClock, Debug::Div1);
  // Debug::OutputClockOnPA8(Debug::HSI, Debug::Div2);
  // Debug::OutputClockOnPA8(Debug::HSI, Debug::Div4);
  // Debug::OutputClockOnPA8(Debug::HSI, Debug::Div8);
  // Debug::OutputClockOnPA8(Debug::HSI, Debug::Div16);
  // Debug::OutputClockOnPA8(Debug::PLLCLK, Debug::Div1);
  // Debug::OutputClockOnPA8(Debug::LSI, Debug::Div1);
  // Debug::OutputClockOnPA8(Debug::MSI, Debug::Div1);
  // Debug::OutputClockOnPA8(Debug::SYSCLK, Debug::Div1);

   /*
    * Inicjalizacja diody.
    */
   GPIO_InitTypeDef LD2_Pin;

   GPIO_StructInit(&LD2_Pin);
   LD2_Pin.GPIO_Pin = GPIO_Pin_5;
   LD2_Pin.GPIO_Mode = GPIO_Mode_OUT;

   GPIO_Init(GPIOA, &LD2_Pin);

   GPIO_SetBits(GPIOA, GPIO_Pin_5);
   /***********************************************
   * USART2 Configuration
   ***********************************************/

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


  char const * string = "Hello World!\n\r";

  /* Infinite loop */
  while (1)
  {
	  send_string_UART2(string);
  }

  return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
extern "C" void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
extern "C" void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
