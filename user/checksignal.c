/**
 * Periodically polls data uplink from the remote controller.
 * The period = PSC/72*period/1000000 (sec)
 */
#include "checksignal.h"
#include "led.h"

u8 dataPID_Last = 250;				

extern u8 dataPID;					// Data packet ID 
extern vu16 remoteControl[4];		// Throttle and direction control from the remote.


void CheckSignal_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_timeBaseStucture;
	TIM_OCInitTypeDef TIM_ocInitStructure;
	
	u16 period 	= 10000;											
	u16 pluse 	= 9000;												
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_timeBaseStucture.TIM_ClockDivision = TIM_CKD_DIV1;      	
	TIM_timeBaseStucture.TIM_Prescaler = 7200-1;                
	TIM_timeBaseStucture.TIM_CounterMode = TIM_CounterMode_Up;		
	TIM_timeBaseStucture.TIM_Period = period;			
	TIM_TimeBaseInit(TIM2,&TIM_timeBaseStucture);
	
	TIM_ocInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				
	TIM_ocInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		
	TIM_ocInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_ocInitStructure.TIM_Pulse =  pluse;							
	TIM_OC1Init(TIM2,&TIM_ocInitStructure);
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);								
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);				
	
	TIM_Cmd(TIM2,ENABLE);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);							
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
}


/**
 * @brief Timer 2 interrupt handler.
 */
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		
		/* Confirm whether PID is calibrated to the set point by the remote */
		if(dataPID_Last == dataPID){				
			if(remoteControl[1]-1250>=800.0){
				remoteControl[1] -= 800;
			}else{
				remoteControl[1] = 1250;
			}
		
			/* When the drone is disconnected from the remote. Set throttle setpoint to 15 by default. */
			remoteControl[2] = 15;						
			remoteControl[3] = 15;					
			LED_Off(LED9);								
		}else{
			/* Drone is connected. */
			dataPID_Last = dataPID;						
		}
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}



