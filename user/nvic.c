#include "nvic.h"

/* Priority Groups */
#define NVIC_PRIORITY_GROUP_3          3 /* Preemption: 4 bits / Subpriority: 0 bits                        */
#define NVIC_PRIORITY_GROUP_4          4 /* Preemption: 3 bits / Subpriority: 1 bits                        */
#define NVIC_PRIORITY_GROUP_5          5 /* Preemption: 2 bits / Subpriority: 2 bits                        */
#define NVIC_PRIORITY_GROUP_6          6 /* Preemption: 1 bits / Subpriority: 3 bits                        */
#define NVIC_PRIORITY_GROUP_7          7 /* Preemption: 0 bits / Subpriority: 4 bits                        */


void NVIC_PriorityConfig(void)
{
	
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 0, 0)); 				//SysTick_IRQn
	NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 1, 0));     		//EXTI15_10_IRQn, IMU external interrupt.
	NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 1, 1));         		//EXTI0_IRQn，NRF24L01's external interrupt.
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_PRIORITY_GROUP_5, 1, 0));					//TIM2_IRQn
}                                                                                           

