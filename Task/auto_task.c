#include "auto_task.h"
#include "led_task.h"
#include "cmsis_os.h"
#include "upper_behaviour.h"
#include "stdbool.h"

extern rc_info_t rc;
extern uint8_t shot_flag;
int flag1_2=1;
// ��������1
void auto_action01_pushring(int*condition) 
{ 	
	//int satisfied;
    // ģ�������жϣ�����ֵ��ʾ�Ƿ���������
		if(*condition == 1)
		{
			shot_flag = 1;
			while(shot_flag)
			{
				Set_SolenoidValve(TuiHuan,1);
			}
				//osDelay(500);
				*condition=2;
		}
    return ;
}

// ��������2
void auto_action02_risering(int* condition) {
	
    if (*condition == 2){
			printf("con\r\n");
			shot_flag = 1;
			while(shot_flag)
			{
				printf("2s\r\n");
				Set_SolenoidValve(PingTai,1);
			}
				//	osDelay(500);			
				  *condition=3;
        return;
    }
    // ִ�в���2�������߼�
}

// ��������3
void auto_action03_hitring(int* condition) {
    if (*condition == 3) {
				shot_flag = 1;
				while(shot_flag)
			{
				upper_feedback_update();
				set_C620moter(0,-90,2.0);
				osDelay(5);
			}
				*condition=4;
        return;
    }
    // ִ�в���3�������߼�
}
void auto_action04_allreset(int* condition) {
    if (*condition == 4) {
	    		Set_SolenoidValve(PingTai,0);
					Set_SolenoidValve(TuiHuan,0);	
					shot_flag = 1;
					while(shot_flag)
				{
					upper_feedback_update();
					set_C620moter(0,60,1.0);
					osDelay(5);
				}
					*condition=0;
					return;
		}
}
void set_condition_start(int* condition){
//	��λ���ذ�
//		 if(rc.ch12==1&&Limits_Up==1)
//	  {
//			*condition=1;
//	  }
			if(rc.ch12==1&&rc.ch10==1)
			*condition=1;
}
void set_condition_judge(int* condition){
		 if(rc.ch12!=1||rc.ch10!=1)
			*condition =0;
}




void auto_task(void
	const * argument)
{
	while(1){
		int condition = 0;  // ��ʼ������
		set_condition_start(&condition);
    // ִ�в���1 
    auto_action01_pushring(&condition);//�ƻ�(rc.ch5=1;) condition = 1
		set_condition_judge(&condition);
		osDelay(50);
    // �ڲ���1֮��ִ�в���2
		//	printf("111\r\n");
			printf("st=%d\r\n,",condition);
    auto_action02_risering(&condition);//ƽ̨���� condition = 2��
		set_condition_judge(&condition);
		osDelay(10);
    // �ڲ���2֮��ִ�в���3
    auto_action03_hitring(&condition);//
		set_condition_judge(&condition);
		osDelay(10);
    // �ڲ���2֮��ִ�в���4
		auto_action04_allreset(&condition);
		set_condition_judge(&condition);
		osDelay(10);
	}
}