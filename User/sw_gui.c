
#include "sw_gui.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"

uint16_t AD_DisVal[20];
uint8_t array[54];	
	
//0x80指令-写一个寄存器
//地址范围为0x00~0xff,所以address是8位的
//参考开发指南-2.2寄存器读写指令 0x80 、0x81
void write_register_80_1byte(uint8_t address,uint8_t data)    
 {
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=0x03;               //指令长度
   array[3]=0x80;
   array[4]=address;
   array[5]=data;               //数值 

   for(i=0;i<6;i++)             //通过串口一发送指令
    {
      HAL_UART_Transmit_DMA(&huart1, array,i);
      //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    } 
 }

//0x80指令-连续写两个寄存器单元 
void write_register_80_2byte(uint8_t address,uint8_t data1,uint8_t data2)                 
 {
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;           
   array[1]=USER_RA;          
   array[2]=0x04;              //指令长度
   array[3]=0x80;
   array[4]=address;
   array[5]=data1;             //数值1
   array[6]=data2;             //数值2

	 
   for(i=0;i<7;i++)            //通过串口一发送指令
    {
      HAL_UART_Transmit_DMA(&huart1, array,i);
      //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    } 
 }


//0x80指令-连续写三个寄存器单元 
void write_register_80_3byte(uint8_t address,uint8_t data1,uint8_t data2,uint8_t data3)
 {
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;           
   array[1]=USER_RA;          
   array[2]=0x05;              //指令长度
   array[3]=0x80;
   array[4]=address;
   array[5]=data1;             //数值1
   array[6]=data2;             //数值2
   array[7]=data3;             //数值3

	 
   for(i=0;i<8;i++)            //通过串口一发送指令
    {
     HAL_UART_Transmit_DMA(&huart1, array,i);
      //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    } 
 } 
 
 
//0x80指令-写多个寄存器
//地址范围为0x00~0xff,所以address是8位的
//参考开发指南-2.2寄存器读写指令 0x80 、0x81
void write_multiple_register_80(uint8_t address,uint8_t data_length,uint8_t *data)    
 {
   uint8_t i,nDataLen;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+1+data_length;   //命令占一字节，地址占一字节，再加上数据长度
   array[3]=0x80;
   array[4]=address;
	 
   for(i=0;i<data_length;i++)
    {
      array[5+i]=data[i]; 
    }
	 
   nDataLen=array[2]+3;        //有效命令的长度
	 
   for(i=0;i<nDataLen;i++)     //通过串口一发送指令
    {
     HAL_UART_Transmit_DMA(&huart1, array,i);
      //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
    } 
 }



//0x82指令-写一个变量存储单元
void write_variable_store_82_1word(uint16_t address,uint16_t data)     
{
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+2;                   //命令占1字节，地址占2字节，再加上数据长度2字节
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;     //取地址的高8位
   array[5]=address&0x00FF;          //取地址的低8位
   array[6]=(data&0xFF00)>>8;        //取数据的高8位
   array[7]=data&0x00FF;             //取数据的低8位
	 
   for(i=0;i<8;i++)                  //通过串口发送指令
   {
     HAL_UART_Transmit_DMA(&huart1, array,i);
     //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
   } 
 }


//0x82指令-连续写两个变量存储单元                    
void write_variable_store_82_2word(uint16_t address,uint16_t data1,uint16_t data2)           
{
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+4;                   //命令占1字节，地址占2字节，再加上数据长度4字节
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;     //取地址的高8位
   array[5]=address&0x00FF;          //取地址的低8位
   array[6]=(data1&0xFF00)>>8;       //取数据的高8位
   array[7]=data1&0x00FF;            //取数据的低8位
   array[8]=(data2&0xFF00)>>8;       //取数据的高8位
   array[9]=data2&0x00FF;            //取数据的低8位
   	 
   for(i=0;i<10;i++)                 //通过串口发送指令
   {
     HAL_UART_Transmit_DMA(&huart1, array,i);
     //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
   } 
 } 
 
 
 
 //0x82指令-连续写两个变量存储单元                    
void write_AD_Value(uint16_t address,uint16_t *data,uint16_t len)           
{
   uint8_t i;
   
	   uint32_t temp;
	 uint32_t tmp_flag = 0;
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+len*2;                   //命令占1字节，地址占2字节，再加上数据长度4字节
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;     //取地址的高8位
   array[5]=address&0x00FF;          //取地址的低8位
	for(i=0;i<len;i++)
	{
   array[i*2+6]=(data[i]&0xFF00)>>8;       //取数据的高8位
   array[i*2+7]=data[i]&0x00FF;            //取数据的低8位
	
	}

	DMA_Usart_Send(array,54);
  
 } 

 //0x82指令-连续写两个变量存储单元                    
void write_PWM_Freq(uint16_t address,uint16_t data1,uint16_t data2)           
{
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+4;                   //命令占1字节，地址占2字节，再加上数据长度4字节
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;     //取地址的高8位
   array[5]=address&0x00FF;          //取地址的低8位
   array[6]=(data1&0xFF00)>>8;       //取数据的高8位
   array[7]=data1&0x00FF;            //取数据的低8位
   array[8]=(data2&0xFF00)>>8;       //取数据的高8位
   array[9]=data2&0x00FF;            //取数据的低8位
   	 
   for(i=0;i<10;i++)                 //通过串口发送指令
   {
     HAL_UART_Transmit_DMA(&huart1, array,i);
    // while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
   } 
 } 
  
//0x82指令-连续写多个变量存储单元
//地址范围为0x0000~0xffff,所以address是16位的
//数据内容是2N字节，因为每个变量存储单元包含2个字节。
//参考开发指南-2.3变量存储器读写指令 0x82 、0x83
void write_multiple_variable_store_82(uint16_t address,uint8_t data_length,uint16_t *data)    
 {
   uint8_t i,nDataLen;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+data_length*2;  //命令占1字节，地址占2字节，再加上数据长度(数据是双字节)
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;         //取地址的高8位
   array[5]=address&0x00FF;              //取地址的低8位

   for(i=0;i<data_length;i++)
    {
      array[6+2*i]=(data[i]&0xFF00)>>8;  //取数据的高8位
      array[7+2*i]=data[i]&0x00FF;       //取数据的低8位
    }

   nDataLen=array[2]+3;                  //有效命令的长度

   HAL_UART_Transmit_DMA(&huart1, array,nDataLen);
 } 
 /* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 