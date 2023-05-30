#ifndef __pid_H
#define __pid_H

#include "stm32f4xx_hal.h"

enum {
    LLAST = 0,                //���ϴ�
    LAST = 1,                 //�ϴ�
    NOW = 2,                  //����

    POSITION_PID,             //λ��ʽPID
    DELTA_PID,                //����ʽPID
};
typedef struct __pid_t {
    float p;                  //Kp
    float i;                  //Ki
    float d;                  //Kd

    float set[3];             //Ŀ��ֵ,����NOW�� LAST�� LLAST���ϴ�
    float get[3];             //����ֵ
    float err[3];             //���

    float pout;               //p���
    float iout;               //i���
    float dout;               //d���

    float pos_out;            //����λ��ʽ���
    float last_pos_out;       //�ϴ�λ��ʽ���
    float delta_u;            //��������ֵ ��
    float delta_out;          //��������ʽ��� = last_delta_out + delta_u
    float last_delta_out;     //�ϴ�����ʽ���

    float max_err;            //������
    float deadband;           //err < deadband return  ����
    uint32_t pid_mode;        //pidģʽ   <λ��ʽ>   <����ʽ>
    uint32_t MaxOutput;       //����޷�
    uint32_t IntegralLimit;   //�����޷�

    void (*f_param_init)(struct __pid_t *pid,  //PID������ʼ��
                         uint32_t pid_mode,
                         uint32_t maxOutput,
                         uint32_t integralLimit,
                         float p,
                         float i,
                         float d);

    void (*f_pid_reset)(struct __pid_t *pid, float p, float i, float d);        //pid���������޸�

} pid_t;

void PID_struct_init(
    pid_t *pid,                      //PID�ṹ��
    uint32_t mode,                   //PIDģʽ (����ʽDELTA_PID,,λ��ʽPOSITION_PID)
    uint32_t maxout,                 //PID������
    uint32_t intergral_limit,        //�����޷�

    float kp,                        //KP ����
    float ki,                        //KI ����
    float kd);                       //KD ΢��

float pid_calc(pid_t *pid, float get, float set);
float pid_dir_calc(pid_t *pid, float get, float set);
void abs_limit(float *a, float ABS_MAX);

#endif
