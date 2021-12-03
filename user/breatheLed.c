/**
 * Controls the LEDs through PWM.
 */

#include "breatheLed.h"
#include "led.h"

u16 i = 11;
u8 flag = 0;
void PWM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_timeBaseStucture;
	TIM_OCInitTypeDef TIM_ocInitStructure;
	
	u16 period 	= 10000;											// PWM Period (ARR)
	u16 pluse 	= 9000;												// PWM pulse width (CCR)

	/* Configure Timer 3 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	

	TIM_timeBaseStucture.TIM_ClockDivision = TIM_CKD_DIV1;      	
	TIM_timeBaseStucture.TIM_Prescaler = 0;                				
	TIM_timeBaseStucture.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_timeBaseStucture.TIM_Period = period;						
	TIM_TimeBaseInit(TIM3,&TIM_timeBaseStucture);
	
	/* Configure Timer 3 PWM channel */
	TIM_ocInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
	TIM_ocInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		
	TIM_ocInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_ocInitStructure.TIM_Pulse = pluse;							
	TIM_OC1Init(TIM3,&TIM_ocInitStructure);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);							
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);			
	
	/* Enable Timer 3 */
	TIM_Cmd(TIM3,ENABLE);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM3,TIM_IT_CC1|TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM3_IRQn);
}


/**
 * @brief Timer 3 interrupt handler.
 */
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_CC1)==SET){
		LED_On(LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8|LED9);
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);
	}else if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET){
		LED_Off(LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8|LED9);
		if(i<10){
			i=10;
			flag = 0;
		}else if(i>9990){
			i=9990;
			flag = 1;
		}
		if(flag == 0){
			TIM_SetCompare1(TIM3,i++);
		}else{
			TIM_SetCompare1(TIM3,i--);
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}




