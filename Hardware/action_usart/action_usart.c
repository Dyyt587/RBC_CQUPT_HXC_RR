#include "action_usart.h"
#include "usart.h"
#include "stdarg.h"
#include "stdio.h"
////��Ч�ʷ���Usart1
//unsigned char UartTxBuf_1[128];
void Usart2Printf(const char *format,...)
{
    unsigned char UartTxBuf[128];
    uint16_t len;
    va_list args;
    va_start(args,format);
    len = vsnprintf((char*)UartTxBuf,sizeof(UartTxBuf),(char*)format,args);
    va_end(args);
    HAL_UART_Transmit(&huart2, UartTxBuf, len,0xff);
}


/*
* ������ HAL��ʵ�ֶമ��ʹ��printf���
* ������ huart����Ӧ�Ĵ��ڽṹ��
* ���أ� ��*/
//void Uart_printf(UART_HandleTypeDef *huart,char *format, ...)
//{
//  unsigned char buf[512]; //������ʱ���飬����ʵ�ʷ��ʹ�С΢��
// uint16_t len;
//  va_list args;
//  va_start(args, format);
//   len = vsnprintf((char *)buf, sizeof(buf), (char *)format+1, args);
//
//   va_end(args);
//  HAL_UART_Transmit(huart,(uint8_t *)buf,len,0xff);

//}