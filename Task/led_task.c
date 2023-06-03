#include "led_task.h"
#include "cmsis_os.h"
#include "upper_behaviour.h"
extern rc_info_t rc;
int flag1_2=1;
void LED_Delay(uint32_t time)
{
    //HAL_Delay(time);
    osDelay(time);
}
void LED_A(uint8_t flag)
{
    if(flag)
        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);
    else
        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
}
void LED_B(uint8_t flag)
{
    if(flag)
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_14,GPIO_PIN_RESET);
    else
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_14,GPIO_PIN_SET);
}
void LED_ALL_OFF()
{
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_SET);
}
void RUN_LED(void)
{
    LED_ALL_OFF();
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_RESET);
    LED_Delay(100);

    LED_ALL_OFF();
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET);
    LED_Delay(100);

    LED_ALL_OFF();
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_RESET);
    LED_Delay(100);

    LED_ALL_OFF();
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_RESET);
    LED_Delay(100);

    LED_ALL_OFF();
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_RESET);
    LED_Delay(100);

    LED_ALL_OFF();
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
    LED_Delay(100);

    LED_ALL_OFF();
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET);
    LED_Delay(100);

    LED_ALL_OFF();
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);
    LED_Delay(100);

}

/**
  * @brief          led RGB任务
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
void led_task(void const * argument)
{
	while(1){
		//RUN_LED();
		if(rc.ch5==3){
		//初始位置
			Set_SolenoidValve(BaoHuan,0);
			Set_SolenoidValve(PingTai,1);
			flag1_2=1;
		}else if(rc.ch5==1){
			Set_SolenoidValve(BaoHuan,1);
			
			
		}else if(rc.ch5==2){
//			Set_SolenoidValve(PingTai,1);
			//推环 送环
			if(flag1_2==1)
			{
				Set_SolenoidValve(TuiHuan,1);
				osDelay(500);
				Set_SolenoidValve(PingTai,0);
				Set_SolenoidValve(TuiHuan,0);
				osDelay(500);
				flag1_2=0;
			}
			
		}
		
//		if(rc.ch5==3){
//		//初始位置
//			Set_SolenoidValve(BaoHuan,0);
//			Set_SolenoidValve(PingTai,0);
//			flag1_2=1;
//		}else if(rc.ch5==1){
//			Set_SolenoidValve(BaoHuan,1);
//			
//			
//		}else if(rc.ch5==2){
//			//推环 送环
//			if(flag1_2==1)
//			{
//				Set_SolenoidValve(TuiHuan,1);
//				osDelay(500);
//				Set_SolenoidValve(PingTai,1);
//				Set_SolenoidValve(TuiHuan,0);
//				osDelay(500);
//				flag1_2=0;
//			}
//			
//		}
    osDelay(50);
	}

}
