
#include "sw_gui.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"

uint16_t AD_DisVal[20];
uint8_t array[54];	
	
//0x80ָ��-дһ���Ĵ���
//��ַ��ΧΪ0x00~0xff,����address��8λ��
//�ο�����ָ��-2.2�Ĵ�����дָ�� 0x80 ��0x81
void write_register_80_1byte(uint8_t address,uint8_t data)    
 {
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=0x03;               //ָ���
   array[3]=0x80;
   array[4]=address;
   array[5]=data;               //��ֵ 

   for(i=0;i<6;i++)             //ͨ������һ����ָ��
    {
      HAL_UART_Transmit_DMA(&huart1, array,i);
      //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    } 
 }

//0x80ָ��-����д�����Ĵ�����Ԫ 
void write_register_80_2byte(uint8_t address,uint8_t data1,uint8_t data2)                 
 {
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;           
   array[1]=USER_RA;          
   array[2]=0x04;              //ָ���
   array[3]=0x80;
   array[4]=address;
   array[5]=data1;             //��ֵ1
   array[6]=data2;             //��ֵ2

	 
   for(i=0;i<7;i++)            //ͨ������һ����ָ��
    {
      HAL_UART_Transmit_DMA(&huart1, array,i);
      //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    } 
 }


//0x80ָ��-����д�����Ĵ�����Ԫ 
void write_register_80_3byte(uint8_t address,uint8_t data1,uint8_t data2,uint8_t data3)
 {
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;           
   array[1]=USER_RA;          
   array[2]=0x05;              //ָ���
   array[3]=0x80;
   array[4]=address;
   array[5]=data1;             //��ֵ1
   array[6]=data2;             //��ֵ2
   array[7]=data3;             //��ֵ3

	 
   for(i=0;i<8;i++)            //ͨ������һ����ָ��
    {
     HAL_UART_Transmit_DMA(&huart1, array,i);
      //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    } 
 } 
 
 
//0x80ָ��-д����Ĵ���
//��ַ��ΧΪ0x00~0xff,����address��8λ��
//�ο�����ָ��-2.2�Ĵ�����дָ�� 0x80 ��0x81
void write_multiple_register_80(uint8_t address,uint8_t data_length,uint8_t *data)    
 {
   uint8_t i,nDataLen;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+1+data_length;   //����ռһ�ֽڣ���ַռһ�ֽڣ��ټ������ݳ���
   array[3]=0x80;
   array[4]=address;
	 
   for(i=0;i<data_length;i++)
    {
      array[5+i]=data[i]; 
    }
	 
   nDataLen=array[2]+3;        //��Ч����ĳ���
	 
   for(i=0;i<nDataLen;i++)     //ͨ������һ����ָ��
    {
     HAL_UART_Transmit_DMA(&huart1, array,i);
      //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
    } 
 }



//0x82ָ��-дһ�������洢��Ԫ
void write_variable_store_82_1word(uint16_t address,uint16_t data)     
{
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+2;                   //����ռ1�ֽڣ���ַռ2�ֽڣ��ټ������ݳ���2�ֽ�
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;     //ȡ��ַ�ĸ�8λ
   array[5]=address&0x00FF;          //ȡ��ַ�ĵ�8λ
   array[6]=(data&0xFF00)>>8;        //ȡ���ݵĸ�8λ
   array[7]=data&0x00FF;             //ȡ���ݵĵ�8λ
	 
   for(i=0;i<8;i++)                  //ͨ�����ڷ���ָ��
   {
     HAL_UART_Transmit_DMA(&huart1, array,i);
     //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
   } 
 }


//0x82ָ��-����д���������洢��Ԫ                    
void write_variable_store_82_2word(uint16_t address,uint16_t data1,uint16_t data2)           
{
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+4;                   //����ռ1�ֽڣ���ַռ2�ֽڣ��ټ������ݳ���4�ֽ�
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;     //ȡ��ַ�ĸ�8λ
   array[5]=address&0x00FF;          //ȡ��ַ�ĵ�8λ
   array[6]=(data1&0xFF00)>>8;       //ȡ���ݵĸ�8λ
   array[7]=data1&0x00FF;            //ȡ���ݵĵ�8λ
   array[8]=(data2&0xFF00)>>8;       //ȡ���ݵĸ�8λ
   array[9]=data2&0x00FF;            //ȡ���ݵĵ�8λ
   	 
   for(i=0;i<10;i++)                 //ͨ�����ڷ���ָ��
   {
     HAL_UART_Transmit_DMA(&huart1, array,i);
     //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
   } 
 } 
 
 
 
 //0x82ָ��-����д���������洢��Ԫ                    
void write_AD_Value(uint16_t address,uint16_t *data,uint16_t len)           
{
   uint8_t i;
   
	   uint32_t temp;
	 uint32_t tmp_flag = 0;
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+len*2;                   //����ռ1�ֽڣ���ַռ2�ֽڣ��ټ������ݳ���4�ֽ�
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;     //ȡ��ַ�ĸ�8λ
   array[5]=address&0x00FF;          //ȡ��ַ�ĵ�8λ
	for(i=0;i<len;i++)
	{
   array[i*2+6]=(data[i]&0xFF00)>>8;       //ȡ���ݵĸ�8λ
   array[i*2+7]=data[i]&0x00FF;            //ȡ���ݵĵ�8λ
	
	}

	DMA_Usart_Send(array,54);
  
 } 

 //0x82ָ��-����д���������洢��Ԫ                    
void write_PWM_Freq(uint16_t address,uint16_t data1,uint16_t data2)           
{
   uint8_t i;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+4;                   //����ռ1�ֽڣ���ַռ2�ֽڣ��ټ������ݳ���4�ֽ�
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;     //ȡ��ַ�ĸ�8λ
   array[5]=address&0x00FF;          //ȡ��ַ�ĵ�8λ
   array[6]=(data1&0xFF00)>>8;       //ȡ���ݵĸ�8λ
   array[7]=data1&0x00FF;            //ȡ���ݵĵ�8λ
   array[8]=(data2&0xFF00)>>8;       //ȡ���ݵĸ�8λ
   array[9]=data2&0x00FF;            //ȡ���ݵĵ�8λ
   	 
   for(i=0;i<10;i++)                 //ͨ�����ڷ���ָ��
   {
     HAL_UART_Transmit_DMA(&huart1, array,i);
    // while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
   } 
 } 
  
//0x82ָ��-����д��������洢��Ԫ
//��ַ��ΧΪ0x0000~0xffff,����address��16λ��
//����������2N�ֽڣ���Ϊÿ�������洢��Ԫ����2���ֽڡ�
//�ο�����ָ��-2.3�����洢����дָ�� 0x82 ��0x83
void write_multiple_variable_store_82(uint16_t address,uint8_t data_length,uint16_t *data)    
 {
   uint8_t i,nDataLen;
   uint8_t array[array_length];
	 
   array[0]=USER_R3;
   array[1]=USER_RA;
   array[2]=1+2+data_length*2;  //����ռ1�ֽڣ���ַռ2�ֽڣ��ټ������ݳ���(������˫�ֽ�)
   array[3]=0x82;
   array[4]=(address&0xFF00)>>8;         //ȡ��ַ�ĸ�8λ
   array[5]=address&0x00FF;              //ȡ��ַ�ĵ�8λ

   for(i=0;i<data_length;i++)
    {
      array[6+2*i]=(data[i]&0xFF00)>>8;  //ȡ���ݵĸ�8λ
      array[7+2*i]=data[i]&0x00FF;       //ȡ���ݵĵ�8λ
    }

   nDataLen=array[2]+3;                  //��Ч����ĳ���

   HAL_UART_Transmit_DMA(&huart1, array,nDataLen);
 } 
 /* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 