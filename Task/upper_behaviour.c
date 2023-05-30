#include "upper_behaviour.h"
extern chassis_move_t upper_Move;

/*
��ŷ�����funtionΪ�ڼ�����ŷ���bool n ��Ӧ��ŷ���ͨ�ض�
SolenoidValve����ŷ�
GPIO��I1 I2 L1 L2
I1��DF1
I2��DF0
L1��PC2
L2:	PB0
*/
void Set_SolenoidValve(int function,int n){
	switch(function){
		case 1:if(n){HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET);}
				else{HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET);}
			break;
		case 2:if(n){HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET);}
				else{HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_RESET);}
			break;
		case 3:if(n){HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);}
				else{HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);}
			break;
		case 4:if(n){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);}
				else{HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);}
			break;
		default:
			
			break;
	}
		
}

/*
˦��һ������ �ƻ�(�ƹ�ȥ�ٻ���)-ƽ̨����-˦�����ת�Ƕ�-��צ�ӽ�-ƽ̨�½�-���ת�Ƕ�-˦�������ת�������ɣ�
*/
void SongHuan(void){
	Set_SolenoidValve(TuiHuan,1);
	osDelay(2000);
	Set_SolenoidValve(PingTai,1);
	Set_SolenoidValve(TuiHuan,0);
	osDelay(500);	
}

/*
speed_siganΪ˿�˵���ٶȻ�Ŀ���ٶ�    angle_paohuanΪ�׻������Ŀ��Ƕ� speed_paohuanΪ�׻������Ŀ���ٶ�
*/
void set_C620moter(float speed_sigan,float angle_paohuan,float speed_paohuan){
		
	
    //����pid
		//˿�˵�����ٶȻ�
		pid_calc(&upper_Move.Wheel_Speed[0].pid_speed,upper_Move.Wheel_Speed[0].speed,speed_sigan);
		//�׻������λ�û�������pid
		pid_calc(&upper_Move.Wheel_Dir[1].pid_pos,upper_Move.Wheel_Dir[1].angle,angle_paohuan);
		pid_calc(&upper_Move.Wheel_Dir[1].pid_speed,upper_Move.Wheel_Dir[1].speed,upper_Move.Wheel_Dir[1].pid_pos.pos_out*speed_paohuan);
    
     
    //���Ϳ��Ƶ���
		set_motor(&hcan2, (int16_t)upper_Move.Wheel_Speed[0].pid_speed.pos_out,
												(int16_t)upper_Move.Wheel_Dir[1].pid_speed.pos_out,
																	0,0,0,0,0,0);


}
void upper_feedback_update(void){
		upper_Move.Wheel_Speed[0].speed = upper_Move.Chassis_Motor_Measure[0]->speed_rpm;
        upper_Move.Wheel_Dir[1].speed = upper_Move.Chassis_Motor_Measure[1]->speed_rpm;
        upper_Move.Wheel_Dir[1].angle = upper_Move.Chassis_Motor_Measure[1]->total_angle*360.0/294876;//294876	
}


