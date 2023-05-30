#ifndef __TASK_H
#define __TASK_H


typedef enum
{
    ROBOT_INIT,                 //��ʼ��
    ROBOT_LOCATE_POSTION_A,     //��λ��Բ��A��
    ROBOT_CORRENT_POSTION_A,    //����λ��Բ��A��
    ROBOT_LOCATE_RINGREGION_A,  //����ȡԲ��A��
    ROBOT_FENTCH_RING,          //ȡ��
    ROBOT_SHOOT_RING,           //�价
    ROBOT_STOP
} robot_behaviour_e;





robot_behaviour_e robot_init(void);
robot_behaviour_e robot_locate_postion_a(void);
robot_behaviour_e robot_corrent_postion_a(void);
robot_behaviour_e robot_locate_ringregion_a(void);
robot_behaviour_e robot_fentch_ring(void);
robot_behaviour_e robot_shoot_ring(void);
robot_behaviour_e robot_stop(void);



#endif
