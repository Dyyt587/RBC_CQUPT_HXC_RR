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
#define speed_sigan rc.ch4*20
#define speed_dahuan 2.5 
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
void set_ch8(void){
		if(rc.ch8==3)
		{	
			Set_SolenoidValve(TuiHuan ,1);
			set_C620moter(speed_sigan,60,1.0);
		}
		else if(rc.ch8==2)
		{
			set_C620moter(speed_sigan,60,1.0);
			Set_SolenoidValve(TuiHuan,0);
		}
		else if(rc.ch8==1)
		{
			set_C620moter(speed_sigan,-90,speed_dahuan);//set_C620moter(speed_sigan,-90,2.0);				
		}

}
void set_ch8_0(void){
		if(rc.ch8==3)
		{	
			Set_SolenoidValve(TuiHuan,1); 
			set_C620moter(0,60,1.0);			
		}
		else if(rc.ch8==2)
		{
			set_C620moter(0,60,1.0);
			Set_SolenoidValve(TuiHuan,0);
		}
		else if(rc.ch8==1)
		{
			set_C620moter(0,-90,speed_dahuan);//	set_C620moter(speed_sigan,-90,2.0);			
		}

}

void test_task(void const * argument)
{
	
	//�Ե���͵�ŷ��Ŀ��ƣ����ϲ�Ŀ���
	//�����ʼ��
	//����˿�˵�����ٶȱջ�
	//����˦�������λ�û����ٶȻ� �ջ�
	upper_Init(&upper_Move);

	
	while(1)
	{//ң��ģʽ
		if(rc.ch10==3){
		/***
		ͨ��			��λ				����
		8					��2				��
		8					��1			����
		8					��3			��λ
		
		7					��2			�ƻ�
		7					��1			��
		7					��3					��λ
		
		PC4				�ߵ�ƽ����		����
		PC5				�ߵ�ƽ����		����
		ch5��ch6 ���ڶ�λ
		
		ch12 �����Զ���
		***/
			upper_feedback_update();
			if(Limits_Down ==0 && Limits_Up ==0)//��������
			{
					set_ch8();
			}else if(Limits_Down ==1)  //��λ���ش��������ޣ�ֻ������
			{
				if(rc.ch4 > 0) //ͨ��4��ģ��ֵ����4��˵��ƽ̨����
				{
					set_ch8();
				}
				else  //������˿��ʧ��
				{
					set_ch8_0();
				}
			}else if(Limits_Up ==1)
			{
				if(rc.ch4 < 0) //ͨ��4��ģ��ֵ<��4��˵��ƽ̨�� xia
				{
					set_ch8();
				}else  //
				{
					set_ch8_0();	
				}					
		  }			
	osDelay(5);
		 //set_ch7
	   	if(rc.ch7==2){
	   	//��ʼλ��
	   		Set_SolenoidValve(BaoHuan,0);
	   		Set_SolenoidValve(PingTai,0);
	   	}else if(rc.ch7==1){
				Set_SolenoidValve(PingTai,1);	
	   	}else if(rc.ch7==3){
	   		Set_SolenoidValve(BaoHuan,1);
	   	}			
	}else
		osDelay(10);

	    	//RUN_LED();
}
}
