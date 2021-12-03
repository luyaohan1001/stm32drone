/**
 * @brief Motor PWM control.
 */
#include "moto_pwm.h"

/**
 * @brief PWM generation initialization.
 */
void motor_PwmConfig(void)
{
	GPIO_InitTypeDef GPIO_initStructure;
	TIM_TimeBaseInitTypeDef TIM_timeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	
	/* Initialize RCC Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_initStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_initStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_initStructure);
	
	/* Enable Timer 1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	/* Timer 1 Count Up ARR */
	TIM_timeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_timeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		
	TIM_timeBaseInitStructure.TIM_Period = PERIOD;						
	TIM_timeBaseInitStructure.TIM_Prescaler = 0;						
	TIM_timeBaseInitStructure.TIM_RepetitionCounter = 0;				
	TIM_TimeBaseInit(TIM1,&TIM_timeBaseInitStructure);
	
	/* Configure output channel. */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;					
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;		
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;		
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	
	TIM_OCInitStructure.TIM_Pulse = 0;									
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);

	/* Enable Timer 1 reload. */
	TIM_ARRPreloadConfig(TIM1,ENABLE);									
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Disable);                  
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Disable);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Disable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Disable);
	
	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}


//方便测试启动电机用的
void motor_Start(void)
{
	motor1_SetDuty(10);
	motor2_SetDuty(10);
	motor3_SetDuty(10);
	motor4_SetDuty(10);
}


/**
 * @brief Set duty cycle of motor 1.
 */
void motor1_SetDuty(u8 precent)
{
	if(precent >= 100){
		precent = 100;
	}
	
	TIM_SetCompare1(TIM1,(u16)(PERIOD*precent/100));
}


/**
 * @brief Set pulse width of motor 1.
 */
void motor1_SetPulse(u16 pulse)
{
	TIM_SetCompare1(TIM1,pulse);
}


/**
 * @brief Set duty cycle of motor 2.
 */
void motor2_SetDuty(u8 precent)
{
	if(precent >= 100){
		precent = 100;
	}
	
	TIM_SetCompare2(TIM1,(u16)(PERIOD*precent/100));
}


/**
 * @brief Set pulse width of motor 2.
 */
void motor2_SetPulse(u16 pulse)
{
	TIM_SetCompare2(TIM1,pulse);
}


/**
 * @brief Set duty cycle of motor 3.
 */
void motor3_SetDuty(u8 precent)
{
	if(precent >= 100){
		precent = 100;
	}
	
	TIM_SetCompare3(TIM1,(u16)(PERIOD*precent/100));
}


/**
 * @brief Set pulse width of motor 3.
 */
void motor3_SetPulse(u16 pulse)
{
	TIM_SetCompare3(TIM1,pulse);
}


/**
 * @brief Set duty cycle of motor 4.
 */
void motor4_SetDuty(u8 precent)
{
	if(precent >= 100){
		precent = 100;
	}
	
	TIM_SetCompare4(TIM1,(u16)(PERIOD*precent/100));
}


/**
 * @brief Set pulse width of motor 4.
 */
void motor4_SetPulse(u16 pulse)
{
	TIM_SetCompare4(TIM1,pulse);
}







