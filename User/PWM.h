#ifndef __PWM_H
#define __PWM_H

#include "main.h"
#include "usart.h"
#include "gpio.h"
//全局变量

void PWM_Freq_DC(uint8_t ch,uint16_t dutycycle, uint16_t freq);
	
#endif

