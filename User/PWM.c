
#include "PWM.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"


void PWM_Freq_DC(uint8_t ch,uint16_t dutycycle, uint16_t freq)
{
	uint16_t arr_peroid,compare_dutycycle,Var_psc=0,i;
	
	uint32_t arr_peroid_long,arr_peroid_long_temp;
	
	/*
	RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
	*/
	
	arr_peroid_long = 160000000/(freq*4);
	arr_peroid_long_temp=arr_peroid_long;
	for(i=0;i<100;i++)
	{
		if(arr_peroid_long_temp>65535)
		{
			Var_psc++;
			arr_peroid_long_temp	=arr_peroid_long/(Var_psc+1);
		}
		else
		{break;}
	}
	
	arr_peroid_long	=arr_peroid_long/	(Var_psc+1);
	arr_peroid = arr_peroid_long;	
	compare_dutycycle = (arr_peroid*dutycycle)/100;
	
	switch (ch)
	{	 	 	 		
		case 0:
		 TIM1->ARR = arr_peroid-1;
		TIM1->PSC =Var_psc;
		TIM1->CCR1 = compare_dutycycle;
		break;
		
		
		case 1:

		TIM2->ARR = arr_peroid-1;
		TIM2->PSC =Var_psc;
		TIM2->CCR1 = compare_dutycycle;
		break;
				
		case 2:
		//TIM3_PWM_Init(arr_peroid,Var_psc);	 //²»·ÖÆµ¡£PWMÆµÂÊ=72000/900=8Khz
		  /* Set the Prescaler value */
		 TIM3->ARR = arr_peroid-1;
		TIM3->PSC =Var_psc;
		TIM3->CCR1 = compare_dutycycle;
		//TIM_SetCompare2(TIM3,compare_dutycycle);	
		break;
						
		case 3:

		TIM4->ARR = arr_peroid-1;
		TIM4->PSC =Var_psc;
		TIM4->CCR1 = compare_dutycycle;
		break;
								
		case 4:
		 TIM9->ARR = arr_peroid-1;
		TIM9->PSC =Var_psc;
		TIM9->CCR1 = compare_dutycycle;
		break;
										
		case 5:
		 TIM10->ARR = arr_peroid-1;
		TIM10->PSC =Var_psc;
		TIM10->CCR1 = compare_dutycycle;
		break;
		
				case 6:
		 TIM11->ARR = arr_peroid-1;
		TIM11->PSC =Var_psc;
		TIM11->CCR1 = compare_dutycycle;
		break;
										
		case 7:
		 TIM12->ARR = arr_peroid-1;
		TIM12->PSC =Var_psc;
		TIM12->CCR1 = compare_dutycycle;
		break;
		
		default:
		break;
		
												
	}

}


 /* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 