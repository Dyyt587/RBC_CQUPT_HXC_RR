
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
//rr�ϲ����  ���and��ŷ�
//������ŷ� �ƻ� �ͻ� �л�
//ͨ��15Ϊ˦���ٶ� 
//ͨ��6Ϊ�綯�ͻ�ƽ̨������ת 
//ͨ��12Ϊ˦���������л� ���� ת�� ������
//ͨ��5Ϊ�ͻ��������ƻ� �����ͻ�ƽ̨��
#define speed_sigan 10000

#define ABS(x)        ((x>0)? (x): (-x))
extern rc_info_t rc;
chassis_move_t upper_Move;
//�ϲ����ĳ�ʼ��
//�ϲ�����������׻����and�������
//��Ȼ��ʼ�� �������ȿ�������
static void upper_Init(chassis_move_t* upper_Move_Init){

	
	if (upper_Move_Init == NULL)
    {
        return;
    }
    //��ȡң����ָ��
    upper_Move_Init->Chassis_RC = get_remote_control_point();
    //��ȡ�ϲ���ָ��
		//4.28����1 ��ȡ���ָ��Ϊcan2 ����Ϊcan1
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
	
	//�Ե���͵�ŷ��Ŀ��ƣ����ϲ�Ŀ���
	//�����ʼ��
	//����˿�˵�����ٶȱջ�
	//����˦�������λ�û����ٶȻ� �ջ�
	upper_Init(&upper_Move);
//	int flag_push=0;
// HEAD
	
	while(1)
	{
		/***
		ͨ��			��λ				����
		6					�µ�				��
		6					�ϵ�				����
		6					�е�				��λ
		
		5					�µ�				�ƻ�
		5					��					��
		5					��					��λ
		
		PC4				�ߵ�ƽ����		����
		PC5				�ߵ�ƽ����		����
		***/
		upper_feedback_update();
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4) ==0 && HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) ==0)//����
			{
						//˿�˺�˦������ 	
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
			}else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4) ==1)  //��λ���ش��������ޣ�ֻ������
			{
				if(rc.ch4 > 0) //ͨ��4��ģ��ֵ����4��˵��ƽ̨����
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
				}else  //������˿��ʧ��
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
				if(rc.ch4 < 0) //ͨ��4��ģ��ֵ<��4��˵��ƽ̨�� xia
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
	    	//��ʼλ��
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
