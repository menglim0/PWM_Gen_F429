#ifndef __SW_GUI_H
#define __SW_GUI_H

#include "main.h"
#include "usart.h"
#include "gpio.h"
//全局变量

#define array_length          100   //定义数组长度 100

#define USER_R3               0xA5  //帧头首字节
#define USER_RA               0x5A  //帧头次字节


#define BUFFER_SIZE_Transmit  0x50  //指令缓冲区大小，用户可根据自己单片机的容量修改

extern uint16_t AD_DisVal[20];

extern void write_register_80_1byte(uint8_t address,uint8_t data);                                //0x80指令-写一个寄存器单元   
extern void write_register_80_2byte(uint8_t address,uint8_t data1,uint8_t data2);                 //0x80指令-连续写两个寄存器单元
extern void write_register_80_3byte(uint8_t address,uint8_t data1,uint8_t data2,uint8_t data3);   //0x80指令-连续写三个寄存器单元
extern void write_multiple_register_80(uint8_t address,uint8_t data_length,uint8_t *data);        //0x80指令-连续写多个寄存器单元

extern void write_variable_store_82_1word(uint16_t address,uint16_t data);                           //0x82指令-写一个变量存储单元
extern void write_variable_store_82_2word(uint16_t address,uint16_t data1,uint16_t data2);           //0x82指令-连续写两个变量存储单元
extern void write_multiple_variable_store_82(uint16_t address,uint8_t data_length,uint16_t *data);   //0x82指令-连续写多个变量存储单元
extern void write_AD_Value(uint16_t address,uint16_t *data,uint16_t len);      

	
#endif

