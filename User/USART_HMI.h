#ifndef __USART_HMI_H
#define __USART_HMI_H

#include "main.h"
#include "usart.h"
#include "gpio.h"
//全局变量
extern uint16_t USART_HMI_DisplayData[8];


void USART_HMI_Display(uint16_t dutycycle[8]);
	
#endif

