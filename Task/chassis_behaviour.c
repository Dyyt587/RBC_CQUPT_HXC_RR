#include "chassis_behaviour.h"


#define CHASSIS_OPEN_RC_SCALE 10 // in CHASSIS_OPEN mode, multiply the value. ��chassis_open ģ���£�ң�������Ըñ������͵�can��


/**
  * @brief          ͨ���жϽ��ٶ����ж���̨�Ƿ񵽴Ｋ��λ��
  * @param          ��Ӧ��Ľ��ٶȣ���λrad/s
  * @param          ��ʱʱ�䣬����GIMBAL_CALI_STEP_TIME��ʱ������
  * @param          ��¼�ĽǶ� rad
  * @param          �����ĽǶ� rad
  * @param          ��¼�ı���ֵ raw
  * @param          �����ı���ֵ raw
  * @param          У׼�Ĳ��� ���һ�� ��һ
  */
#define chassis_cali_gyro_judge(gyro, cmd_time, angle_set, angle, ecd_set, ecd, step) \
    {                                                                                \
        if ((gyro) < GIMBAL_CALI_GYRO_LIMIT)                                         \
        {                                                                            \
            (cmd_time)++;                                                            \
            if ((cmd_time) > GIMBAL_CALI_STEP_TIME)                                  \
            {                                                                        \
                (cmd_time) = 0;                                                      \
                (angle_set) = (angle);                                               \
                (ecd_set) = (ecd);                                                   \
                (step)++;                                                            \
            }                                                                        \
        }                                                                            \
    }





static void chassis_zero_force_control(fp32 *vx_can_set, fp32 *vy_can_set, fp32 *wz_can_set, chassis_move_t *chassis_move_rc_to_vector)
{
    if (vx_can_set == NULL || vy_can_set == NULL || wz_can_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }
    *vx_can_set = 0.0f;
    *vy_can_set = 0.0f;
    *wz_can_set = 0.0f;
}
static void chassis_no_move_control(fp32 *Vx_Set, fp32 *Vy_Set, fp32 *Vw_Set, chassis_move_t *Chassis_Move_Rc_to_Vector)
{
    if (Vx_Set == NULL || Vy_Set == NULL || Vw_Set == NULL || Chassis_Move_Rc_to_Vector == NULL)
    {
        return;
    }



    if(Chassis_Move_Rc_to_Vector->Chassis_RC->ch6 == 1)
    {
        *Vx_Set = 0.0f;
        *Vy_Set = 0.0f;
        *Vw_Set = 0.0f;

    }
    if(Chassis_Move_Rc_to_Vector->Chassis_RC->ch6 == 3)
    {
        *Vx_Set =4000;
    }

    if(Chassis_Move_Rc_to_Vector->Chassis_RC->ch6 == 2)
    {
        *Vx_Set =8000;
    }
}

static void chassis_remote_move_control(fp32 *Vx_Set, fp32 *Vy_Set, fp32 *Vw_Set, chassis_move_t *Chassis_Move_Rc_to_Vector)
{
    if (Vx_Set == NULL || Vy_Set == NULL || Vw_Set == NULL || Chassis_Move_Rc_to_Vector == NULL)
    {
        return;
    }


    *Vx_Set = Chassis_Move_Rc_to_Vector->Chassis_RC->ch1 *CHASSIS_OPEN_RC_SCALE;
    *Vy_Set = Chassis_Move_Rc_to_Vector->Chassis_RC->ch2 *CHASSIS_OPEN_RC_SCALE;
    *Vw_Set = Chassis_Move_Rc_to_Vector->Chassis_RC->ch3 *CHASSIS_OPEN_RC_SCALE;







    return;
}



static void chassis_local_move_control(fp32 *Vx_Set, fp32 *Vy_Set, fp32 *Vw_Set, chassis_move_t *Chassis_Move_Rc_to_Vector)
{
	if (Vx_Set == NULL || Vy_Set == NULL || Vw_Set == NULL || Chassis_Move_Rc_to_Vector == NULL)
    {
        return;
    }


		switch(Chassis_Move_Rc_to_Vector->Chassis_RC->ch6) 
		{
			case 1:
				*Vx_Set =0;
			  *Vy_Set =0;
			  *Vw_Set =0;
			
				break;
			case 2:
				*Vx_Set =0;
			  *Vy_Set =0;
			  *Vw_Set =90;
			break;
			case 3:
				
				*Vx_Set =100;
			  *Vy_Set =0;
			  *Vw_Set =0;
			break;
			
		}

    return;
}


//���⣬���������Ϊģʽ����

//ע��Ϊ��Ӧdjiң�������ճ�ch5��Ĭ��Ϊң��ģʽ
//Ϊ�˱��ڲ��ԣ��ֽ���ע�͵�
chassis_behaviour_mode_e Chassis_Behaviour_Mode; //= CHASSIS_REMOTE_MOVE;

/**
  * @brief          ͨ���߼��жϣ���ֵ"chassis_behaviour_mode"������ģʽ
  * @param[in]      chassis_move_mode: ��������
  * @retval         none
  */
void chassis_behaviour_mode_set(chassis_move_t *Chassis_Move_Mode)
{
    if (Chassis_Move_Mode == NULL)
    {
        return;
    }

    //������Ϊģʽѡ��һ�����̿���ģʽ
    //����Լ����߼��жϽ�����ģʽ
		//�������һ��
		//ͨ����һ��������������
		//ͨ�����������������λ
		//ͨ����������������ң��
    if(Chassis_Move_Mode->Chassis_RC->ch5 == 1)
    {
        Chassis_Behaviour_Mode = CHASSIS_ZERO_FORCE;
    }
//    else if(Chassis_Move_Mode->Chassis_RC->ch5 == 2)
//    {
//        Chassis_Behaviour_Mode = CHASSIS_NO_MOVE;
//    }
    else if(Chassis_Move_Mode->Chassis_RC->ch5 == 2)
    {
        Chassis_Behaviour_Mode = CHASSIS_LOCATING_MOVE;
    }
    else if(Chassis_Move_Mode->Chassis_RC->ch5 ==3)
    {
        Chassis_Behaviour_Mode = CHASSIS_REMOTE_MOVE;
    }


    //������Ϊģʽѡ��һ�����̿���ģʽ
    if (Chassis_Behaviour_Mode == CHASSIS_ZERO_FORCE) //����
    {
        Chassis_Move_Mode->Chassis_Mode = CHASSIS_ZERO_FORCE;
    }
    else if (Chassis_Behaviour_Mode == CHASSIS_NO_MOVE) //�̶�
    {
        Chassis_Move_Mode->Chassis_Mode = CHASSIS_NO_MOVE;
    }
    else if (Chassis_Behaviour_Mode == CHASSIS_LOCATING_MOVE) //��λ
    {
        Chassis_Move_Mode->Chassis_Mode = CHASSIS_LOCATING_MOVE;
    }
    else if (Chassis_Behaviour_Mode == CHASSIS_REMOTE_MOVE) //ң��
    {
        Chassis_Move_Mode->Chassis_Mode = CHASSIS_REMOTE_MOVE;
    }

}

//	 CHASSIS_ZERO_FORCE,                   //��������, ��û�ϵ�����
//  CHASSIS_NO_MOVE,                      //���̱��ֲ���
//	 CHASSIS_LOCATING_MOVE,                //���̶�λ
//	 CHASSIS_REMOTE_MOVE                   //ң�ؿ���
void chassis_behaviour_control_set(fp32 *Vx_Set, fp32 *Vy_Set, fp32 *Vw_Set, chassis_move_t *Chassis_Move_Rc_To_Vector)
{
    if (Vx_Set == NULL || Vy_Set == NULL || Vw_Set == NULL || Chassis_Move_Rc_To_Vector == NULL)
    {

        return;
    }
    //������Ϊģʽѡ��һ�����̿���ģʽ

    if (Chassis_Behaviour_Mode == CHASSIS_ZERO_FORCE)  //��������, ��û�ϵ�����
    {

        chassis_zero_force_control(Vx_Set, Vy_Set, Vw_Set, Chassis_Move_Rc_To_Vector);
    }
    else	 if (Chassis_Behaviour_Mode == CHASSIS_NO_MOVE)  //�̶����� ���ƶ�
    {
        chassis_no_move_control(Vx_Set, Vy_Set, Vw_Set, Chassis_Move_Rc_To_Vector);
    }
    else if (Chassis_Behaviour_Mode == CHASSIS_LOCATING_MOVE)//���̶�λ��ע��Ŷ
    {
			chassis_local_move_control(Vx_Set, Vy_Set, Vw_Set, Chassis_Move_Rc_To_Vector);

    }
    else if (Chassis_Behaviour_Mode == CHASSIS_REMOTE_MOVE)
    {
        chassis_remote_move_control(Vx_Set, Vy_Set, Vw_Set, Chassis_Move_Rc_To_Vector);
    }


    //ң��������ģʽ
    //����̨��ĳЩģʽ�£����ʼ���� ���̲���
//    if (gimbal_cmd_to_chassis_stop())
//    {
//        chassis_behaviour_mode = CHASSIS_NO_MOVE;
//    }

}


