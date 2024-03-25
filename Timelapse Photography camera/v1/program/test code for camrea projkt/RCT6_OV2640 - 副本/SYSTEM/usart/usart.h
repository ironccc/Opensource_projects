#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART1_REC_LEN  	200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define USART2_REC_LEN  	200  	//定义最大接收字节数 200
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口2接收
	
#define USART3_REC_LEN  	200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口3接收
	
//LORA
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;         		//接收状态标记	

//DEBUG
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         		//接收状态标记	
extern u8 U2_RECEIVE_STA;

//TO 6818
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         		//接收状态标记	

//如果想串口中断接收，请不要注释以下宏定义
void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
u8 UART1_SendByte(u8 ch);
u8 UART2_SendByte(u8 ch);
u8 UART3_SendByte(u8 ch);
void USART2SendStr(char* str);

void at_cmd_8266(char* fmt,...) ;
#endif


