#ifndef _CONTROL_H
#define _CONTROL_H

#include "stm32f10x.h"

void Get_Angle(void);
void Direction_Control(void);
void Outter_PID(void);
void Inner_PID(void);
void Rotation_Correction(void);
void Set_Pwm(void);
void DealPwm(void);

#endif

