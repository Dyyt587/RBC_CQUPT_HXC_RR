#include "auto_task.h"
#include "led_task.h"
#include "cmsis_os.h"
#include "upper_behaviour.h"
#include "stdbool.h"

extern rc_info_t rc;
extern uint8_t shot_flag;
int flag1_2=1;
// 操作函数1
void auto_action01_pushring(int*condition) 
{ 	
	//int satisfied;
    // 模拟条件判断，返回值表示是否满足条件
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

// 操作函数2
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
    // 执行操作2的其他逻辑
}

// 操作函数3
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
    // 执行操作3的其他逻辑
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
//	限位开关版
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
		int condition = 0;  // 初始化条件
		set_condition_start(&condition);
    // 执行操作1 
    auto_action01_pushring(&condition);//推环(rc.ch5=1;) condition = 1
		set_condition_judge(&condition);
		osDelay(50);
    // 在操作1之后执行操作2
		//	printf("111\r\n");
			printf("st=%d\r\n,",condition);
    auto_action02_risering(&condition);//平台上升 condition = 2；
		set_condition_judge(&condition);
		osDelay(10);
    // 在操作2之后执行操作3
    auto_action03_hitring(&condition);//
		set_condition_judge(&condition);
		osDelay(10);
    // 在操作2之后执行操作4
		auto_action04_allreset(&condition);
		set_condition_judge(&condition);
		osDelay(10);
	}
}