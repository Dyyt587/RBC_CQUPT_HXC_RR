
#include "led_task.h"
#include "cmsis_os.h"
#include "test_task.h"
#include "bsp_as5048.h"
#include "bsp_can.h"
#include "bsp_sbus.h"
#include "chassis_behaviour.h"
#include "stdio.h"
#include "pid.h"
#include "upper_behaviour.h"
#include "led_task.h"
#include "math.h"
//rr上层控制  电机and电磁阀
//三个电磁阀 推环 送环 夹环
//通道15为甩环速度 
//通道6为电动送环平台的正反转 
//通道12为甩环动作（夹环 蓄力 转动 丢环）
//通道5为送环动作（推环 气动送环平台）
#define speed_sigan 10000

#define ABS(x)        ((x>0)? (x): (-x))
extern rc_info_t rc;
chassis_move_t upper_Move;
//上层电机的初始化
//上层两个电机，抛环电机and上升电机
//虽然初始化 但可能先开环试试
static void upper_Init(chassis_move_t* upper_Move_Init){

	
	if (upper_Move_Init == NULL)
    {
        return;
    }
    //获取遥控器指针
    upper_Move_Init->Chassis_RC = get_remote_control_point();
    //获取上层电机指针
		//4.28错误1 获取电机指针为can2 接线为can1
    for(uint8_t i=0; i<8; i++)
    {
        upper_Move_Init->Chassis_Motor_Measure[i] = get_upper_motor_measure_point(i);
    }
		 for (uint8_t i = 0; i < 4; i++)
    {
		 
        PID_struct_init(&upper_Move_Init->Wheel_Speed[i].pid_speed,POSITION_PID, 10000, 2000,
                        5.0f, 0.04f, 0.0f);
        PID_struct_init(&upper_Move_Init->Wheel_Dir[i].pid_pos,POSITION_PID, 10000, 2000,
                        100.0f, 0.00f, 10.0);
        PID_struct_init(&upper_Move_Init->Wheel_Dir[i].pid_speed,POSITION_PID, 10000, 2000,
                        4.5f, 0.08f, 1.5f);
    }
    PID_struct_init(&upper_Move_Init->chassis_angle_pid, POSITION_PID, 20000, 2000,
                    500.f, 0.00f, 0.01);
}


void test_task(void const * argument)
{
	
	//对电机和电磁阀的控制，即上层的控制
	//电机初始化
	//对于丝杆电机，速度闭环
	//对于甩环电机，位置环，速度环 闭环
	upper_Init(&upper_Move);
//	int flag_push=0;
// HEAD
	
	while(1)
	{
		/***
		通道			档位				功能
		6					下档				打环
		6					上档				升环
		6					中档				复位
		
		5					下档				推环
		5					上					抱
		5					中					复位
		
		PC4				高电平出发		下限
		PC5				高电平触发		上限
		***/
		upper_feedback_update();
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4) ==0 && HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) ==0)//下限
			{
						//丝杆和甩环调节 	
					if(rc.ch6==1)
					{	
						Set_SolenoidValve(TuiHuan,1);
						set_C620moter(rc.ch4*20,0,1.0);  
					}
					else if(rc.ch6==3)
					{
						set_C620moter(rc.ch4*20,60,1.0);
						Set_SolenoidValve(TuiHuan,0);
					}
					else if(rc.ch6==2)
					{
						set_C620moter(rc.ch4*20,-90,2.0);					
					}
			}else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4) ==1)  //限位开关触碰到下限，只能往上
			{
				if(rc.ch4 > 0) //通道4的模拟值大于4，说明平台往上
				{
					if(rc.ch6==1){	
						Set_SolenoidValve(TuiHuan,1);
						set_C620moter(rc.ch4*20,0,1.0);  
					}
					else if(rc.ch6==3){
						set_C620moter(rc.ch4*20,60,1.0);
						Set_SolenoidValve(TuiHuan,0);
					}
					else if(rc.ch6==2){
						set_C620moter(rc.ch4*20,-90,2.0);					
					}
				}else  //往下让丝杆失灵
				{
					if(rc.ch6==1){	 
						Set_SolenoidValve(TuiHuan,1);
						set_C620moter(0,0,1.0);  
					}
					else if(rc.ch6==3){
						set_C620moter(0,60,1.0);
						Set_SolenoidValve(TuiHuan,0);
					}
					else if(rc.ch6==2){
						set_C620moter(0,-90,2.0);					
					}					
				}
			}else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) ==1)
			{
				if(rc.ch4 < 0) //通道4的模拟值<于4，说明平台往 xia
				{
					if(rc.ch6==1){	
						Set_SolenoidValve(TuiHuan,1);
						set_C620moter(rc.ch4*20,0,1.0);  
					}
					else if(rc.ch6==3){
						set_C620moter(rc.ch4*20,60,1.0);
						Set_SolenoidValve(TuiHuan,0);
					}
					else if(rc.ch6==2){
						set_C620moter(rc.ch4*20,-90,2.0);					
					}
				}else  //
				{
					if(rc.ch6==1){	 
						Set_SolenoidValve(TuiHuan,1);
						set_C620moter(0,0,1.0);  
					}
					else if(rc.ch6==3){
						set_C620moter(0,60,1.0);
						Set_SolenoidValve(TuiHuan,0);
					}
					else if(rc.ch6==2){
						set_C620moter(0,-90,2.0);					
					}					
				}				
			}

		

		
	    	//RUN_LED();
	    	if(rc.ch5==3){
	    	//初始位置
	    		Set_SolenoidValve(BaoHuan,0);
	    		Set_SolenoidValve(PingTai,0);
	    	}else if(rc.ch5==1){
//	    		Set_SolenoidValve(BaoHuan,1);
	    		
	    	}else if(rc.ch5==2){
	    		Set_SolenoidValve(PingTai,1);
	    		
	    		
	    	}
			
			
			//	
//		if(rc.ch6==1){set_C620moter(rc.ch4*20,-60,0);}
//		if(rc.ch6==2){set_C620moter(rc.ch4*20,60,0);} 
		
		
//		if(rc.ch7==1){
//			set_C620moter(rc.ch4*20,-60,0);	
//			flag_push=1;
//			if(ABS(upper_Move.Chassis_Motor_Measure[1]->total_angle-10)<1.0){
//					HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_RESET);
//			}
//		}
//		else if(rc.ch7==3){
//			set_C620moter(rc.ch4*20,0,0);
//			if(ABS(upper_Move.Chassis_Motor_Measure[1]->total_angle-0)<1.0){
//					HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET);		
//			}
//			flag_push=0;
//		}
//		else if(rc.ch7==2){
//				if(flag_push==0){
//				set_C620moter(rc.ch4*20,60,0);
//			}			
//				flag_push=0;
//		}
//		else if(rc.ch8==1){
//		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET);
//		}
//		else if(rc.ch8==2){
//			printf("this is ch==2\r\n");
//		}else if(rc.ch8==3){
//		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET);
//		}
//		
//		
//		else if(rc.ch11==1){
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);
//		}
//		else if(rc.ch11==2){
//			printf("this is ch==2\r\n");
//		}else if(rc.ch8==3){
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
//		}	
//		
//		
//		else if(rc.ch9==1){
//		
//		}
//		else if(rc.ch9==2){
//			printf("this is ch==2\r\n");
//		}else if(rc.ch9==3){
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
//		}	
//		else{
//		printf("this is else \r\n");
//		}
//		
//		
		
		osDelay(10);
	}
	
}
