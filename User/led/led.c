/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "sw_gui.h"
#include "PWM.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "lcd.h"
#include "stdlib.h" 
#include "delay.h"
#include "display.h"
#include "led.h"



LED_Str LED[4]=
{
	{		GPIOD,
		  GPIO_PIN_8	},
	
	{		GPIOD,
		  GPIO_PIN_9	},
	

	{		GPIOD,
		  GPIO_PIN_10	},

		
	{		GPIOD,
		  GPIO_PIN_11  }

};

void LED_TOGGLE(LED_Str LED)
{
	
	HAL_GPIO_TogglePin(LED.Port,LED.Pin);
}

void LED_SET(LED_Str LED)
{
	
	HAL_GPIO_WritePin(LED.Port,LED.Pin,1);
}

void LED_RESET(LED_Str LED)
{
	
	HAL_GPIO_WritePin(LED.Port,LED.Pin,0);
}




