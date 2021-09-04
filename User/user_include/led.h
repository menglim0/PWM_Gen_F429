#ifndef __LED_H
#define __LED_H			

#include "main.h"

typedef struct 
{
   GPIO_TypeDef  *Port;
	uint16_t Pin;	
	
} LED_Str;

extern LED_Str LED[4];
extern void LED_TOGGLE(LED_Str LED);
extern void LED_SET(LED_Str LED);
extern void LED_RESET(LED_Str LED);

#endif
