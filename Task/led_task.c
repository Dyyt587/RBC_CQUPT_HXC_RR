#include "led_task.h"
#include "cmsis_os.h"
#include "upper_behaviour.h"
#include "stdbool.h"

extern rc_info_t rc;
extern uint8_t shot_flag;
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

// �����жϺ���ʾ��


// ��������1
void auto_action01_pushring(int condition) 
{ 	
	//int satisfied;
    // ģ�������жϣ�����ֵ��ʾ�Ƿ���������
		if(condition == 1)
		{
			shot_flag = 1;
			while(shot_flag)
			{
				Set_SolenoidValve(TuiHuan,1);
			}
				//osDelay(500);
				condition=2;
		}
//		else
//		{
//			condition=0;
//		}
		
    return ;
}

// ��������2
void auto_action02_risering(int condition) {
	
    if (condition == 2) {
			printf("con\r\n");
			shot_flag = 1;
			while(shot_flag)
			{
				printf("2s\r\n");
				Set_SolenoidValve(PingTai,1);
			}
				//	osDelay(500);			
				  condition++;
        return;
    }
    // ִ�в���2�������߼�
}

// ��������3
void auto_action03_hitring(int condition) {
    if (condition == 3) {
			set_C620moter(0,-90,2.0);
				condition++;
        return;
    }
    // ִ�в���3�������߼�
}
void auto_action04_allreset(int condition) {
    if (condition == 4) {
			set_C620moter(0,60,1.0);
	    		Set_SolenoidValve(PingTai,0);
					Set_SolenoidValve(TuiHuan,0);	
				condition=0;
        return;
    }
    // ִ�в���3�������߼�
}
int* set_condition_start(int* condition){
		 if(rc.ch5==1&&Limits_Up==1)
	  {
			*condition=1;
	  }
}
int* set_condition_judge(int* condition){
		 if(rc.ch5!=1)
			*condition=0;
}

/**
  * @brief          led RGB����
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
void led_task(void
	const * argument)
{
	while(1)
		{
			
    int condition = 0;  // ��ʼ������
		set_condition_start(&condition);
    // ִ�в���1 
    auto_action01_pushring(condition);//�ƻ�(rc.ch5=1;) condition = 1
		//set_condition_judge(&condition);
		osDelay(50);
    // �ڲ���1֮��ִ�в���2
		//	printf("111\r\n");
			printf("st=%d\r\n,",condition);
    auto_action02_risering(condition);//ƽ̨���� condition = 2��
		set_condition_judge(&condition);
    // �ڲ���2֮��ִ�в���3
//    auto_action03_hitring(condition);//
//		set_condition_judge(&condition);
//    // �ڲ���2֮��ִ�в���4
//		auto_action04_allreset(condition);
//		set_condition_judge(&condition);
	//	RUN_LED();
		osDelay(500);
	}

}

