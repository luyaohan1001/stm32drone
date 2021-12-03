/**
 * @brief Initialize the external interrupt of MPU6050 IMU.
 */
#include "dmp_exti.h"

void DMP_EXTIConfig(void)
{
	GPIO_InitTypeDef GPIO_initStructure;
	EXTI_InitTypeDef EXTI_initStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_initStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA,&GPIO_initStructure);
	
	EXTI_initStructure.EXTI_Line = EXTI_Line15;
	EXTI_initStructure.EXTI_LineCmd = ENABLE;
	EXTI_initStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_initStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_initStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);	
	NVIC_EnableIRQ(EXTI15_10_IRQn);									
}



