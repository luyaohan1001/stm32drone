#ifndef _MOTOR_PWM_H
#define _MOTOR_PWM_H

#include "stm32f10x.h"

#define PERIOD 		(SystemCoreClock/10000)				//ARR计数值为：7200，不分频时，则pwm频率为10KHz，注意这里要用小括号括起来


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
