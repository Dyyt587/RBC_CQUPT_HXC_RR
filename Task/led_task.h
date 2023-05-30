#ifndef __LED_TASK_H
#define __LED_TASK_H

#include "main.h"
#include "struct_typedef.h"

/**
  * @brief          led rgb task
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
/**
  * @brief          led RGBÈÎÎñ
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
extern void led_task(void const * argument);
void LED_ALL_OFF(void);
void RUN_LED(void);

#endif


