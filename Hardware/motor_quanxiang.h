#ifndef _MOTERQUANXIANG_H
#define _MOTERQUANXIANG_H

#include "pid.h"


#define M1 1
#define M2 2
#define M3 3
#define M4 4

#define M5 5
#define M6 6
#define M7 7
#define M8 8
#define MAll 9


typedef struct
{
    int id;
    pid_t pid_pos; //ÿ������ת���λ�û�
    pid_t pid_speed;  //ÿ�����ֵ��ٶȻ�
    float speed;      //�����ٶ�
    float rpm;        //ת����Ȧ
} Speed_wheel;



void Wheel_Init(void);

void setSingleMotor_speed(uint8_t _mNum, float _mspeed);  //���õ��������ٶ�------������
//���õ��������ٶ�
void setMotors(float speedM1, float speedM2, float speedM3); //ÿ����ֵ��ٶ� ��speed����ǰ�� ���������


#endif
