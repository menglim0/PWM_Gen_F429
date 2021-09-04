
#include "PWM.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "USART_HMI.h"

uint16_t USART_HMI_DisplayData[8]={0};

void USART_HMI_Display(uint16_t display[8])
{
		printf("n0.val=%d\xff\xff\xff",aRxBuffer[1]+(aRxBuffer[0]<<8));
		printf("n1.val=%d\xff\xff\xff",display[0]);
		printf("n2.val=%d\xff\xff\xff",display[1]);
		printf("n3.val=%d\xff\xff\xff",display[2]);
		printf("n4.val=%d\xff\xff\xff",display[3]);
		printf("n5.val=%d\xff\xff\xff",display[4]);
		printf("n6.val=%d\xff\xff\xff",display[5]);
		printf("n7.val=%d\xff\xff\xff",display[6]);
		printf("n8.val=%d\xff\xff\xff",display[7]);
//		
		
}



 /* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 