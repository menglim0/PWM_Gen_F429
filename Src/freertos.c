/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

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
#include "USART_HMI.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define ChannelLength 8
uint32_t Duty[ChannelLength],Freq[ChannelLength],T_index,AD_Result[24];
uint32_t EC18_Duty[ChannelLength],EC18_Freq[ChannelLength];
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId_t defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
    
    uint8_t index;
	  uint8_t LED_index=0;

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	//	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 );
		LED_TOGGLE(LED[LED_index]);
		LED_index++;
		if(LED_index>=4)
		{
			LED_index=0;
		}
		//DMA_Usart_Send(AD_TransValue, 48);	
		for(index=0;index<24;index++)
		{
		
			if(index<16)
			{AD_ConvertVal[index]=(AD_ConvertVal[index]*10)/62;}
			else
			{AD_ConvertVal[index]=(AD3_ConvertVal[index-16]*10)/62;}
			
			AD_Result[index]=AD_ConvertVal[index]*62/20;
			
		}
		//write_AD_Value(0x0201,AD_ConvertVal,24);		
		//DMA_Usart_Send(AD_TransValue, 48);
		
		if(recv_end_flag == 1)   //接收完成标志
    {
			//write_AD_Value(0x0201,AD_ConvertVal,24);
        
			
        rx_len = 0;//清除计数
        recv_end_flag = 0;//清除接收结束标志位
        //memset(rx_buffer,0,sizeof(rx_buffer));
    } 
		for(index=0;index<ChannelLength;index++)
		{
					Duty[index]=(AD_Result[index*2+0]*100)/2047;
					Freq[index]=(AD_Result[index*2+1])*2;
			
		}
		

		/*
		ECU18 信号发生器处理*/
//		K93	  1.3-12k Hz，占空比50%+		PWM1_1 AMS
					EC18_Duty[0]=50; //0-100
					EC18_Freq[0]=Freq[0]*3; //0-4096*4
		if(EC18_Freq[0]>12000)
		{
			EC18_Freq[0]=12000;
	
		}
		else if(EC18_Freq[0]>1300)
		{
		EC18_Freq[0]=1300;
		}
			
		USART_HMI_DisplayData[0]=EC18_Freq[0];
//		K91	       19Hz，占空比范围80-10%		PWM1_2&&PWM1_3	IATS(per)IATS	

		EC18_Duty[1]=Duty[1]; //0-100
		EC18_Freq[1]=19; //0-4096*4
		
		if(EC18_Duty[1]>80)
		{
			EC18_Duty[1]=80;
			
		}
		else if(EC18_Duty[1]<10)
		{
			EC18_Duty[1]=10;
	
		}
				USART_HMI_DisplayData[1]=EC18_Duty[1];
		
				EC18_Duty[2]=Duty[2]; //0-100
		EC18_Freq[2]=19; //0-4096*4
		
		if(EC18_Duty[2]>80)
		{
			EC18_Duty[2]=80;

		}
		else if(EC18_Duty[2]<10)
		{
			EC18_Duty[2]=10;

		}
				USART_HMI_DisplayData[2]=EC18_Duty[2];
//		K90	0-100hz，占空比固定50%		PWM1_4   VSS
		EC18_Duty[3]=50; //0-100
		EC18_Freq[3]=Freq[3]/40; //0-4096*4
			if(EC18_Freq[3]>100)
		{
			EC18_Freq[3]=100;
			
		}
		USART_HMI_DisplayData[3]=EC18_Freq[3];
//		K92	频率0-5Khz，占空比固定50%		PWM2_1  FSS
//		K49	频率0-5Khz，占空比固定50%		PWM2_2   GLW
//		K94	频率0-5Khz，占空比固定50%		PWM2_3   SPARE1
//		K28	频率0-5Khz，占空比固定50%		PWM2_4   SPARE2		
		for(index=4;index<ChannelLength;index++)
		{
				EC18_Duty[index]=50; //0-100
				EC18_Freq[index]=Freq[index]*5/4; //0-4096*4
				if(EC18_Freq[index]>5000)
			{
				EC18_Freq[index]=5000;
				
			}
			USART_HMI_DisplayData[index]=EC18_Freq[index];
		}

//	

	
		for(index=0;index<ChannelLength;index++)
		{
					T_index=index;

				PWM_Freq_DC(T_index,EC18_Duty[index],EC18_Freq[index]);
				//display_Ch_Fre_Duty(index,Freq[T_index],Duty[T_index]);	
			
			
		}
		
		USART_HMI_Display(USART_HMI_DisplayData);
	/*	PWM_Freq_DC(0,20,500);
		PWM_Freq_DC(1,40,800);
		PWM_Freq_DC(2,60,1000);
		PWM_Freq_DC(3,80,1200);
		
		
		PWM_Freq_DC(4,20,1000);
		PWM_Freq_DC(5,40,800);
		PWM_Freq_DC(6,60,1000);
		PWM_Freq_DC(7,80,1200);*/
		/**/
    osDelay(50);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
