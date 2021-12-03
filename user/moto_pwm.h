#ifndef _MOTOR_PWM_H
#define _MOTOR_PWM_H

#include "stm32f10x.h"

#define PERIOD 		(SystemCoreClock/10000)			


void motor_PwmConfig(void);
void motor_Start(void);

void motor1_SetDuty(u8 precent);
void motor2_SetDuty(u8 precent);
void motor3_SetDuty(u8 precent);
void motor4_SetDuty(u8 precent);

void motor1_SetPulse(u16 pulse);
void motor2_SetPulse(u16 pulse);
void motor3_SetPulse(u16 pulse);
void motor4_SetPulse(u16 pulse);

#endif
