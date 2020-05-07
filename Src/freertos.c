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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint32_t Duty[8],Freq[8],T_index,AD_Result[24];

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

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_12|GPIO_PIN_13);
		
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
		for(index=0;index<8;index++)
		{
					Duty[index]=(AD_Result[index*2+0]*100)/2047;
					Freq[index]=(AD_Result[index*2+1])*2;
		}
		
		
		
		for(index=0;index<8;index++)
		{
					T_index=index;

				PWM_Freq_DC(T_index,Duty[index],Freq[index]);
			
		}
	/*	PWM_Freq_DC(0,20,500);
		PWM_Freq_DC(1,40,800);
		PWM_Freq_DC(2,60,1000);
		PWM_Freq_DC(3,80,1200);
		
		
		PWM_Freq_DC(4,20,1000);
		PWM_Freq_DC(5,40,800);
		PWM_Freq_DC(6,60,1000);
		PWM_Freq_DC(7,80,1200);*/
		/**/
    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
