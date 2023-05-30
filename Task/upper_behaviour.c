#include "upper_behaviour.h"
extern chassis_move_t upper_Move;

/*
电磁阀控制funtion为第几个电磁阀，bool n 对应电磁阀开通关断
SolenoidValve：电磁阀
GPIO：I1 I2 L1 L2
I1：DF1
I2：DF0
L1：PC2
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
甩环一套流程 推环(推过去再回来)-平台上升-甩环电机转角度-夹爪加紧-平台下降-电机转角度-甩环（电机转加气缸松）
*/
void SongHuan(void){
	Set_SolenoidValve(TuiHuan,1);
	osDelay(2000);
	Set_SolenoidValve(PingTai,1);
	Set_SolenoidValve(TuiHuan,0);
	osDelay(500);	
}

/*
speed_sigan为丝杆电机速度环目标速度    angle_paohuan为抛环电机的目标角度 speed_paohuan为抛环电机的目标速度
*/
void set_C620moter(float speed_sigan,float angle_paohuan,float speed_paohuan){
		
	
    //计算pid
		//丝杆电机的速度环
		pid_calc(&upper_Move.Wheel_Speed[0].pid_speed,upper_Move.Wheel_Speed[0].speed,speed_sigan);
		//抛环电机的位置环，串级pid
		pid_calc(&upper_Move.Wheel_Dir[1].pid_pos,upper_Move.Wheel_Dir[1].angle,angle_paohuan);
		pid_calc(&upper_Move.Wheel_Dir[1].pid_speed,upper_Move.Wheel_Dir[1].speed,upper_Move.Wheel_Dir[1].pid_pos.pos_out*speed_paohuan);
    
     
    //发送控制电流
		set_motor(&hcan2, (int16_t)upper_Move.Wheel_Speed[0].pid_speed.pos_out,
												(int16_t)upper_Move.Wheel_Dir[1].pid_speed.pos_out,
																	0,0,0,0,0,0);


}
void upper_feedback_update(void){
		upper_Move.Wheel_Speed[0].speed = upper_Move.Chassis_Motor_Measure[0]->speed_rpm;
        upper_Move.Wheel_Dir[1].speed = upper_Move.Chassis_Motor_Measure[1]->speed_rpm;
        upper_Move.Wheel_Dir[1].angle = upper_Move.Chassis_Motor_Measure[1]->total_angle*360.0/294876;//294876	
}


