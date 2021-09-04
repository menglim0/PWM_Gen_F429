/*-------------------------------------------------------------------------------
文件名称：led.c
文件描述：根据硬件连接配置LED端口，打开对应的寄存器        
备    注：无
---------------------------------------------------------------------------------*/
#include "delay.h"
#include "sys.h"
#include "lcd.h"

static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数

void delay_init()	 
{
	fac_us=16000000/8000000;	//为系统时钟的1/8  
	fac_ms=(u16)fac_us*1000;//非ucos下,代表每个ms需要的systick时钟数   

}								    


/*延时：1毫秒的i倍*/
void delay(int i)               
{
	int j,k;
	for(j=0;j<i;j++)
		for(k=0;k<1100;k++);
}


/*延时：1us的i倍*/
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



