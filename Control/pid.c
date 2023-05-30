/**
  ******************************************************************************
  * @file			pid.c
  * @version		V1.0.0
  * @date			2022��12��11��
  * @brief   		����PID�� ����/����ϰ���Խ�get/measure/real/fdb,
						  ��������һ���set/target/ref
  *******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "pid.h"
//#include "mytype.h"
#include <math.h>
//#include "cmath"

#define ABS(x)        ((x>0)? (x): (-x))

void abs_limit(float *a, float ABS_MAX) {
    if (*a > ABS_MAX)
        *a = ABS_MAX;
    if (*a < -ABS_MAX)
        *a = -ABS_MAX;
}

/*������ʼ��--------------------------------------------------------------*/
static void pid_param_init(
    pid_t *pid,                           //PID�ṹ��
    uint32_t mode,                        //PIDģʽ (����ʽDELTA_PID,,λ��ʽPOSITION_PID)POSITION_PID,
    uint32_t maxout,                      //PID������
    uint32_t intergral_limit,             //�����޷�
    float kp,                             //KP ����
    float ki,                             //KI ����
    float kd)                             //KD ΢��
{
    pid->IntegralLimit = intergral_limit;
    pid->MaxOutput = maxout;
    pid->pid_mode = mode;

    pid->p = kp;
    pid->i = ki;
    pid->d = kd;
}

/*��;���Ĳ����趨(����)------------------------------------------------------------*/
static void pid_reset(pid_t *pid, float kp, float ki, float kd) {
    pid->p = kp;
    pid->i = ki;
    pid->d = kd;
}

/**
 *
 * @param pid pid�ṹ��
 * @param get ����ֵ
 * @param set Ŀ��ֵ
 * @return
 */
float pid_calc(pid_t *pid, float get, float set) {
    pid->get[NOW] = get;                //����ֵ
    pid->set[NOW] = set;                //Ŀ��ֵ
    pid->err[NOW] = set - get;          //set - measure Ŀ��ֵ-����ֵ

    //������� �� �����ж�
    if (pid->max_err != 0 && ABS(pid->err[NOW]) > pid->max_err)
        return 0;
    if (pid->deadband != 0 && ABS(pid->err[NOW]) < pid->deadband)
        return 0;

    //λ��ʽp
    if (pid->pid_mode == POSITION_PID) {
        pid->pout = pid->p * pid->err[NOW];
        pid->iout += pid->i * pid->err[NOW];
        pid->dout = pid->d * (pid->err[NOW] - pid->err[LAST]);
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->pos_out = pid->pout + pid->iout + pid->dout;
        abs_limit(&(pid->pos_out), pid->MaxOutput);
        pid->last_pos_out = pid->pos_out;    //update last time
    }
    //����ʽP
    else if (pid->pid_mode == DELTA_PID) {
        pid->pout = pid->p * (pid->err[NOW] - pid->err[LAST]);
        pid->iout = pid->i * pid->err[NOW];
        pid->dout = pid->d * (pid->err[NOW] - 2 * pid->err[LAST] + pid->err[LLAST]);
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->delta_u = pid->pout + pid->iout + pid->dout;
        pid->delta_out = pid->last_delta_out + pid->delta_u;
        abs_limit(&(pid->delta_out), pid->MaxOutput);
        pid->last_delta_out = pid->delta_out;    //update last time
    }
    //����
    pid->err[LLAST] = pid->err[LAST];
    pid->err[LAST] = pid->err[NOW];
    pid->get[LLAST] = pid->get[LAST];
    pid->get[LAST] = pid->get[NOW];
    pid->set[LLAST] = pid->set[LAST];
    pid->set[LAST] = pid->set[NOW];
    return pid->pid_mode == POSITION_PID ? pid->pos_out : pid->delta_out;

}

float pid_dir_calc(pid_t *pid, float get, float set) {
    pid->get[NOW] = get;  						//����ֵ
    pid->set[NOW] = set;                //Ŀ��ֵ
    pid->err[NOW] = set - get;          //set - measure Ŀ��ֵ-����ֵ

    //������� �� �����ж�
    if (pid->max_err != 0 && ABS(pid->err[NOW]) > pid->max_err)
        return 0;
    if (pid->deadband != 0 && ABS(pid->err[NOW]) < pid->deadband)
        return 0;

    //λ��ʽp
    if (pid->pid_mode == POSITION_PID) {
        pid->pout = pid->p * pid->err[NOW];
        pid->iout += pid->i * pid->err[NOW];
        pid->dout = pid->d * (pid->err[NOW] - pid->err[LAST]);
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->pos_out = pid->pout + pid->iout + pid->dout;
					if(ABS(set - get)<ABS(get - set))
					pid->pos_out=pid->pos_out;
					else pid->pos_out=-pid->pos_out;			
			
        abs_limit(&(pid->pos_out), pid->MaxOutput);
        pid->last_pos_out = pid->pos_out;    //update last time
    }
    //����ʽP
    else if (pid->pid_mode == DELTA_PID) {
        pid->pout = pid->p * (pid->err[NOW] - pid->err[LAST]);
        pid->iout = pid->i * pid->err[NOW];
        pid->dout = pid->d * (pid->err[NOW] - 2 * pid->err[LAST] + pid->err[LLAST]);
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->delta_u = pid->pout + pid->iout + pid->dout;
        pid->delta_out = pid->last_delta_out + pid->delta_u;
        abs_limit(&(pid->delta_out), pid->MaxOutput);
        pid->last_delta_out = pid->delta_out;    //update last time
    }
    //����
    pid->err[LLAST] = pid->err[LAST];
    pid->err[LAST] = pid->err[NOW];
    pid->get[LLAST] = pid->get[LAST];
    pid->get[LAST] = pid->get[NOW];
    pid->set[LLAST] = pid->set[LAST];
    pid->set[LAST] = pid->set[NOW];
    return pid->pid_mode == POSITION_PID ? pid->pos_out : pid->delta_out;

}

/**
    *@bref. special calculate position PID @attention @use @gyro data!!
						�������λ��PID @ע��@ʹ��@��������!!
    *@param[in] set�� target
    *@param[in] real	measure
    */
float pid_sp_calc(pid_t *pid, float get, float set, float gyro) {
    pid->get[NOW] = get;
    pid->set[NOW] = set;
    pid->err[NOW] = set - get;    //set - measure

    if (pid->pid_mode == POSITION_PID) //λ��ʽp
    {
        pid->pout = pid->p * pid->err[NOW];
        if (fabs(pid->i) >= 0.001f)
            pid->iout += pid->i * pid->err[NOW];
        else
            pid->iout = 0;
        pid->dout = -pid->d * gyro / 100.0f;
        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->pos_out = pid->pout + pid->iout + pid->dout;
        abs_limit(&(pid->pos_out), pid->MaxOutput);
        pid->last_pos_out = pid->pos_out;    //update last time
    } else if (pid->pid_mode == DELTA_PID)//����ʽP
    {
        pid->pout = pid->p * (pid->err[NOW] - pid->err[LAST]);
        pid->iout = pid->i * pid->err[NOW];
        pid->dout = pid->d * (pid->err[NOW] - 2 * pid->err[LAST] + pid->err[LLAST]);

        abs_limit(&(pid->iout), pid->IntegralLimit);
        pid->delta_u = pid->pout + pid->iout + pid->dout;
        pid->delta_out = pid->last_delta_out + pid->delta_u;
        abs_limit(&(pid->delta_out), pid->MaxOutput);
        pid->last_delta_out = pid->delta_out;    //update last time
    }

    pid->err[LLAST] = pid->err[LAST];
    pid->err[LAST] = pid->err[NOW];
    pid->get[LLAST] = pid->get[LAST];
    pid->get[LAST] = pid->get[NOW];
    pid->set[LLAST] = pid->set[LAST];
    pid->set[LAST] = pid->set[NOW];
    return pid->pid_mode == POSITION_PID ? pid->pos_out : pid->delta_out;
}

/*pid�����ʼ��-----------------------------------------------------------------*/
void PID_struct_init(
    pid_t *pid,                    //PID�ṹ��
    uint32_t mode,                 //PIDģʽ (����ʽDELTA_PID,,λ��ʽPOSITION_PID)
    uint32_t maxout,               //PID������
    uint32_t intergral_limit,      //�����޷�

    float kp,                      //KP ����
    float ki,                      //KI ����
    float kd)                      //KD ΢��
{
    /*init function pointer		����ָ��  f_param_init  f_pid_reset */
    pid->f_param_init = pid_param_init;        //PID������ʼ��	void (*f_param_init)
    pid->f_pid_reset = pid_reset;              //pid���������޸�	void (*f_pid_reset)

    pid->dout = 0;
    pid->iout = 0;
    pid->dout = 0;

    pid->pos_out = 0;
    pid->last_pos_out = 0;

    pid->delta_u = 0;
    pid->delta_out = 0;

    pid->last_delta_out = 0;
    pid->dout = 0;

    /*init pid param */
    pid->f_param_init(pid, mode, maxout, intergral_limit, kp, ki, kd);
}
