#ifndef __SW_GUI_H
#define __SW_GUI_H

#include "main.h"
#include "usart.h"
#include "gpio.h"
//ȫ�ֱ���

#define array_length          100   //�������鳤�� 100

#define USER_R3               0xA5  //֡ͷ���ֽ�
#define USER_RA               0x5A  //֡ͷ���ֽ�


#define BUFFER_SIZE_Transmit  0x50  //ָ�������С���û��ɸ����Լ���Ƭ���������޸�

extern uint16_t AD_DisVal[20];

extern void write_register_80_1byte(uint8_t address,uint8_t data);                                //0x80ָ��-дһ���Ĵ�����Ԫ   
extern void write_register_80_2byte(uint8_t address,uint8_t data1,uint8_t data2);                 //0x80ָ��-����д�����Ĵ�����Ԫ
extern void write_register_80_3byte(uint8_t address,uint8_t data1,uint8_t data2,uint8_t data3);   //0x80ָ��-����д�����Ĵ�����Ԫ
extern void write_multiple_register_80(uint8_t address,uint8_t data_length,uint8_t *data);        //0x80ָ��-����д����Ĵ�����Ԫ

extern void write_variable_store_82_1word(uint16_t address,uint16_t data);                           //0x82ָ��-дһ�������洢��Ԫ
extern void write_variable_store_82_2word(uint16_t address,uint16_t data1,uint16_t data2);           //0x82ָ��-����д���������洢��Ԫ
extern void write_multiple_variable_store_82(uint16_t address,uint8_t data_length,uint16_t *data);   //0x82ָ��-����д��������洢��Ԫ
extern void write_AD_Value(uint16_t address,uint16_t *data,uint16_t len);      

	
#endif

