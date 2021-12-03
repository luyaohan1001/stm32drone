#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"


#define LED1		1
#define LED2		2
#define LED3		4
#define LED4		8
#define LED5		16
#define LED6		32
#define LED7		64
#define LED8		128
#define LED9		256


void LED_Config(void);
void LED_On(u16 LEDx);
void LED_Off(u16 LEDx);
void LED_Toggle(u16 LEDx);
void LED_CyclieOn(u32 delayms);

#endif
