#ifndef __TEST_TASK_H
#define __TEST_TASK_H

#include "main.h"
#include "struct_typedef.h"
//#define up_touched (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))
//#define up_untouched (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))

//#define down_touched (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))
//#define down_untouched (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))
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
extern void test_task(void const * argument);

#endif


