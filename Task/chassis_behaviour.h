#ifndef __CHASSIS_BEHAVIOUR_H
#define __CHASSIS_BEHAVIOUR_H
#include "chassis_task.h"
//#include "motor.h"
#include "pid.h"
#include "bsp_sbus.h"
#include "bsp_can.h"
typedef float fp32;
typedef double fp64;




typedef struct
{
    int id;
    pid_t pid_pos;      //ÿ������ת���λ�û�
    pid_t pid_speed;    //ÿ�����ֵ��ٶȻ�
    float speed;        //�����ٶ�
    float speed_set;    //�����ٶ�
    int16_t give_current; //��ֵ����ֵ
    float rpm;          //ת����Ȧ
} wheel_speed_t;

typedef struct
{
    int id;
    pid_t pid_pos;      //ÿ������ת���λ�û�
    pid_t pid_speed;    //ÿ�����ֵ��ٶȻ�
    float speed;        //�����ٶ�
    float speed_set;    //�����ٶ�
    float angle;        //��ǰ�Ƕ�
    float angle_set;    //�趨�Ƕ�
    int16_t give_current; //��ֵ����ֵ

    float rpm;          //ת����Ȧ

} wheel_dir_t;




typedef enum
{
    CHASSIS_ZERO_FORCE,                   //��������, ��û�ϵ�����
    CHASSIS_NO_MOVE,                      //���̱��ֲ���
    CHASSIS_LOCATING_MOVE,                //���̶�λ
    CHASSIS_REMOTE_MOVE                   //ң�ؿ���
} chassis_behaviour_mode_e;

/*******����ģ��*********/
typedef enum
{
    Omni3_Car,
    Omni4_Car,
    Wheel3_Car,
    Wheel4_Car
} chassis_kinematics_mode_e;

typedef struct
{

//  const gimbal_motor_t *chassis_yaw_motor;   //will use the relative angle of yaw gimbal motor to calculate the euler angle.����ʹ�õ�yaw��̨�������ԽǶ���������̵�ŷ����.
//  const gimbal_motor_t *chassis_pitch_motor; //will use the relative angle of pitch gimbal motor to calculate the euler angle.����ʹ�õ�pitch��̨�������ԽǶ���������̵�ŷ����
//  const fp32 *chassis_INS_angle;             //the point to the euler angle of gyro sensor.��ȡ�����ǽ������ŷ����ָ��

//  chassis_mode_e last_chassis_mode;          //last state machine.�����ϴο���״̬��
//  chassis_motor_t motor_chassis[4];          //chassis motor data.���̵������
//  pid_type_def motor_speed_pid[4];             //motor speed PID.���̵���ٶ�pid
//  pid_type_def chassis_angle_pid;              //follow angle PID.���̸���Ƕ�pid

//  first_order_filter_type_t chassis_cmd_slow_set_vx;  //use first order filter to slow set-point.ʹ��һ�׵�ͨ�˲������趨ֵ
//  first_order_filter_type_t chassis_cmd_slow_set_vy;  //use first order filter to slow set-point.ʹ��һ�׵�ͨ�˲������趨ֵ


    const rc_info_t *Chassis_RC;               //����ʹ�õ�ң����ָ��, the point to remote control
    const motor_measure_t *Chassis_Motor_Measure[8];
    chassis_behaviour_mode_e Chassis_Mode;               //state machine. ���̿���״̬��
    chassis_behaviour_mode_e Last_Chassis_Mode;          //last state machine.�����ϴο���״̬��
    chassis_kinematics_mode_e Chassis_Kinematics_Mode;   //�����˶�ѧģ��

    wheel_speed_t Wheel_Speed[4] ;				//������
    wheel_dir_t   Wheel_Dir[4]   ;           //������
    pid_t chassis_angle_pid;
    fp32 Vx;                          //�����ٶ� ǰ������ ǰΪ������λ m/s
    fp32 Vy;                          //�����ٶ� ���ҷ��� ��Ϊ��  ��λ m/s
    fp32 Vw;                          //������ת���ٶȣ���ʱ��Ϊ�� ��λ rad/s
    fp32 Vx_Set;                      //�����趨�ٶ� ǰ������ ǰΪ������λ m/s
    fp32 Vy_Set;                      //�����趨�ٶ� ���ҷ��� ��Ϊ������λ m/s
    fp32 Vw_Set;                      //�����趨��ת���ٶȣ���ʱ��Ϊ�� ��λ rad/s

    fp32 Vx_Max_Speed;   //ǰ����������ٶ� ��λm/s
    fp32 Vx_Min_Speed;   //���˷�������ٶ� ��λm/s
    fp32 Vy_Max_Speed;   //��������ٶ� ��λm/s
    fp32 Vy_Min_Speed;   //�ҷ�������ٶ� ��λm/s


    fp32 Chassis_Yaw;    //����yaw�Ƕ�
    fp32 Chassis_Yaw_Set;//�����趨yaw�Ƕ�
    fp32 Postion_X;   //
    fp32 Postion_Y;
    fp32 Postion_X_Set;   //
    fp32 Postion_Y_Set;
} chassis_move_t;



void chassis_behaviour_mode_set(chassis_move_t *Chassis_Move_Mode);
void chassis_behaviour_control_set(fp32 *Vx_Set, fp32 *Vy_Set, fp32 *Angle_Set, chassis_move_t *Chassis_Move_Rc_To_Vector);



#endif
