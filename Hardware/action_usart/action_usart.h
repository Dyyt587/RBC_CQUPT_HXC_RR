#ifndef _MYUSART_H
#define _MYUSART_H

#include "main.h"

void Uart_printf(UART_HandleTypeDef *huart,char *format, ...);
void Usart2Printf(const char *format,...);

#endif
