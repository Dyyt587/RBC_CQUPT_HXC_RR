#include "motor_quanxiang.h"
#include "can.h"
#include "bsp_can.h"
const int offsetm1 = 1; //´ú±íË³Ê±Õë
const int offsetm2 = 1; //´ú±íÄæÊ±Õë
const int offsetm3 = 1;
const int offsetm4 = 1;

Speed_wheel S_wheel[4]= {0};				//Çý¶¯ÂÖ

void Limit(float *a, float MAX)
{
    if (*a > MAX)
        *a = MAX;
    if (*a < -MAX)
        *a = -MAX;
}
void Wheel_Init(void)
{
    PID_struct_init(&S_wheel[0].pid_speed,POSITION_PID, 10000, 2000,
                    1.50f, 0.00f, 0.0);
    PID_struct_init(&S_wheel[0].pid_pos,POSITION_PID, 20000, 2000,
                    1.0f, 0.00f, 0.0f);

    PID_struct_init(&S_wheel[1].pid_speed,POSITION_PID, 10000, 2000,
                    1.50f, 0.00f, 0.01);
    PID_struct_init(&S_wheel[1].pid_pos,POSITION_PID, 20000, 2000,
                    1.0f, 0.00f, 0.0f);

    PID_struct_init(&S_wheel[2].pid_speed,POSITION_PID, 10000, 2000,
                    1.50f, 0.00f, 0.01f);
    PID_struct_init(&S_wheel[2].pid_pos,POSITION_PID, 20000, 2000,
                    1.0f, 0.00f, 0.0f);
	
		PID_struct_init(&S_wheel[3].pid_speed,POSITION_PID, 10000, 2000,
                    1.50f, 0.00f, 0.01f);
    PID_struct_init(&S_wheel[3].pid_pos,POSITION_PID, 20000, 2000,
                    1.0f, 0.00f, 0.0f);

}

//ÉèÖÃµ¥¸öÂÖ×ÓËÙ¶È------Çý¶¯ÂÖ
void setSingleMotor_speed(uint8_t _mNum, float _mspeed)
{
    //ÏÞ·ù
    //Limit(&_mspeed, ABS_MAX);
    //ÅÐ¶ÏÊÇÄÄ¸öÂÖ×Ó
    switch(_mNum)
    {
    case M1:
        pid_calc(&S_wheel[0].pid_speed, motor_can1[0].speed_rpm, offsetm1 * _mspeed);
        break;
    case M2:
        pid_calc(&S_wheel[1].pid_speed, motor_can1[1].speed_rpm, offsetm2 * _mspeed);
        break;
    case M3:
        pid_calc(&S_wheel[2].pid_speed, motor_can1[2].speed_rpm, offsetm3 * _mspeed);
        break;
		case M4:
        pid_calc(&S_wheel[3].pid_speed, motor_can1[3].speed_rpm, offsetm4 * _mspeed);
        break;
    default:
        break;
    }
}


void setMotors(float speedM1, float speedM2, float speedM3) //Ã¿¸ö¶ÂÖµÄËÙ¶È Õýspeed´ú±íÇ°½ø ¸º´ú±íºóÍË
{
    setSingleMotor_speed(M1, speedM1);
    setSingleMotor_speed(M2, speedM2);
    setSingleMotor_speed(M3, speedM3);
		setSingleMotor_speed(M3, speedM3);
	
    set_motor_A(&hcan1,
                S_wheel[0].pid_speed.pos_out,
                S_wheel[1].pid_speed.pos_out,
                S_wheel[2].pid_speed.pos_out,
                S_wheel[3].pid_speed.pos_out);

}







