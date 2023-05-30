#ifndef __UPPER_BEHAVIOUR_H
#define __UPPER_BEHAVIOUR_H

#include "led_task.h"
#include "cmsis_os.h"
#include "test_task.h"
#include "bsp_as5048.h"
#include "bsp_can.h"
#include "bsp_sbus.h"
#include "chassis_behaviour.h"
#include "stdio.h"
#include "pid.h"
#include "led_task.h"


void SongHuan(void);
void Set_SolenoidValve(int function,int n);
void set_C620moter(float speed_sigan,float angle_paohuan,float speed_paohuan);
void upper_feedback_update(void);

#define JiaZhua 4   //I1
#define BaoHuan 2	//I2
#define TuiHuan 3	//L1
#define PingTai 1	//L2

#endif


