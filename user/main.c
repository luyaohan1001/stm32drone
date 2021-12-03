#include "stm32f10x.h"
#include "mpu_dmp_useapi.h"
#include "usart.h"
#include "i2c_moni.h"
#include "dmp_exti.h"
#include "nvic.h"
#include "mpu6050_i2cmoni.h"
#include "led.h"
#include "moto_pwm.h"
#include "systick.h"
#include "control.h"
#include "nRF.h"
#include "checksignal.h"


int main(void)
{
	USART_Config();
	printf("usart is ready\r\n");
	

	NVIC_PriorityConfig();
	
	SysTick_init();
	
	LED_Config();
	LED_On(LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8);
	
	/* Initialize I2C */
	I2C_MoniConfig();
	
	/* Initialize MPU6050 */
	mpu_dmp_init();
	SetReportFlag(RESET,RESET);
	
	/* Initialize Motors */
	MOTO_PwmConfig();
	
	NRF_Config();
	CheckSignal_Config();
	DMP_EXTIConfig();
 
	while(1){}
}

