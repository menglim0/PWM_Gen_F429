/*-------------------------------------------------------------------------------
�ļ����ƣ�led.c
�ļ�����������Ӳ����������LED�˿ڣ��򿪶�Ӧ�ļĴ���        
��    ע����
---------------------------------------------------------------------------------*/
#include "delay.h"
#include "sys.h"
#include "lcd.h"

static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������

void delay_init()	 
{
	fac_us=16000000/8000000;	//Ϊϵͳʱ�ӵ�1/8  
	fac_ms=(u16)fac_us*1000;//��ucos��,����ÿ��ms��Ҫ��systickʱ����   

}								    


/*��ʱ��1�����i��*/
void delay(int i)               
{
	int j,k;
	for(j=0;j<i;j++)
		for(k=0;k<1100;k++);
}


/*��ʱ��1us��i��*/
void delay_us(int i)               
{
	int j,k;
	for(j=0;j<i+10;j++)
		for(k=0;k<1;k++);
}



void delay_ms(uint16_t i)
{	 		  	  
	uint32_t temp;		   
	uint16_t j,k;
	for(j=0;j<i*2000;j++)
		for(k=0;k<5;k++); 	    
} 



