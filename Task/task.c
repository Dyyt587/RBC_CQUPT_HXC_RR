#include "task.h"
#include "stdio.h"
#define int_abs(x) ((x) > 0 ? (x) : (-x))

//typedef enum
//{
//    ROBOT_INIT,                 //��ʼ��
//    ROBOT_LOCATE_POSTION_A,     //��λ��Բ��A��
//    ROBOT_CORRENT_POSTION_A,    //����λ��Բ��A��
//    ROBOT_LOCATE_RINGREGION_A,  //����ȡԲ��A��
//    ROBOT_FENTCH_RING,          //ȡ��
//	   ROBOT_SHOOT_RING,           //�价
//    ROBOT_STOP
//} robot_behaviour_e;




robot_behaviour_e  Robot_Behaviours = ROBOT_INIT;      //��ǰѭ��������(״̬����)״̬
robot_behaviour_e  Robot_nowBehaviours = ROBOT_INIT;   //��ǰ״̬
robot_behaviour_e  Robot_lastBehaviours = ROBOT_INIT;  //�ϴ�״̬(���ڼ�¼ǰһ״̬������״̬����Դ)

int  g_WorkLoopCnt=0;

robot_behaviour_e robot_init(void)
{
    robot_behaviour_e nextBehaviours = ROBOT_INIT;


    if(1)   //��ʼ���ӽ��� ������һ״̬
    {

        nextBehaviours = ROBOT_LOCATE_POSTION_A;

    }

    return nextBehaviours;
}


robot_behaviour_e robot_locate_postion_a(void)
{
    robot_behaviour_e nextBehaviours = ROBOT_LOCATE_POSTION_A;
    if(1)
    {

        nextBehaviours = ROBOT_CORRENT_POSTION_A;
    }
    return nextBehaviours;
}


robot_behaviour_e robot_corrent_postion_a(void)
{
    robot_behaviour_e nextBehaviours = ROBOT_CORRENT_POSTION_A;
    if(1)
    {

        nextBehaviours = ROBOT_LOCATE_RINGREGION_A;
    }
    return nextBehaviours;
}

robot_behaviour_e robot_locate_ringregion_a(void)
{
    robot_behaviour_e nextBehaviours = ROBOT_LOCATE_RINGREGION_A;
    if(1)
    {

        nextBehaviours = ROBOT_FENTCH_RING;
    }
    return nextBehaviours;
}


robot_behaviour_e robot_fentch_ring(void)
{
    robot_behaviour_e nextBehaviours = ROBOT_FENTCH_RING;
    if(1)
    {

        nextBehaviours = ROBOT_SHOOT_RING;
    }
    return nextBehaviours;
}


robot_behaviour_e robot_shoot_ring(void)
{
    robot_behaviour_e nextBehaviours = ROBOT_SHOOT_RING;
    if(1)
    {

        // nextBehaviours = ROBOT_CORRENT_POSTION_A;
    }
    return nextBehaviours;
}


//    ROBOT_INIT,                 //��ʼ��
//    ROBOT_LOCATE_POSTION_A,     //��λ��Բ��A��
//    ROBOT_CORRENT_POSTION_A,    //����λ��Բ��A��
//    ROBOT_LOCATE_RINGREGION_A,  //����ȡԲ��A��
//    ROBOT_FENTCH_RING,          //ȡ��
//	   ROBOT_SHOOT_RING,           //�价
//    ROBOT_STOP

robot_behaviour_e robot_stop(void)
{
    robot_behaviour_e nextBehaviours = ROBOT_STOP;

    switch (Robot_lastBehaviours)
    {
    case ROBOT_INIT:
        nextBehaviours = ROBOT_INIT;
        printf("resume...\r\n");
        break;
    case ROBOT_LOCATE_POSTION_A:
        nextBehaviours = ROBOT_LOCATE_POSTION_A;
        printf("resume...\r\n");
        break;
    case ROBOT_CORRENT_POSTION_A:
        nextBehaviours = ROBOT_CORRENT_POSTION_A;
        printf("resume...\r\n");
        break;
    case ROBOT_LOCATE_RINGREGION_A:
        nextBehaviours = ROBOT_LOCATE_RINGREGION_A;
        printf("resume...\r\n");
        break;
    case ROBOT_FENTCH_RING:
        nextBehaviours = ROBOT_FENTCH_RING;
        printf("resume...\r\n");
        break;
    case ROBOT_SHOOT_RING:
        nextBehaviours = ROBOT_SHOOT_RING;
        printf("resume...\r\n");
        break;
    default:
        break;
    }

}













void robot_run_loop()
{
    switch(Robot_Behaviours)
    {
    /*������ʼ���Լ�*/
    case ROBOT_INIT:
        //	g_washerStatus = washer_do_init();
        Robot_Behaviours=  robot_init();
        break;

    /*��λ��λ��A*/
    case ROBOT_LOCATE_POSTION_A:
        Robot_Behaviours=  robot_locate_postion_a();
        break;

    /*����λ��A����*/
    case ROBOT_CORRENT_POSTION_A:
        Robot_Behaviours=  robot_corrent_postion_a();
        break;

    /*����ȡ����*/
    case ROBOT_LOCATE_RINGREGION_A:
        Robot_Behaviours=  robot_locate_ringregion_a();
        break;
    /*ȡ��*/
    case ROBOT_FENTCH_RING:
        Robot_Behaviours=  robot_fentch_ring();
        break;
    /*�价*/
    case ROBOT_SHOOT_RING:
        Robot_Behaviours=  robot_shoot_ring();
        break;
    /*ͣ*/
    case ROBOT_STOP:
        Robot_Behaviours=  robot_stop();
        break;
    default:
        break;
    }

    if (Robot_Behaviours != Robot_nowBehaviours)
    {
        Robot_lastBehaviours = Robot_nowBehaviours;
        Robot_nowBehaviours = Robot_Behaviours;
    }
}
