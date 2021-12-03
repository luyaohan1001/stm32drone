/**
* Configuration and interface to the USART peripheral.
*/
#include "usart.h"

//#define USE_USART1					
#define USART						USART3
#define RCC_PORT					RCC_APB2Periph_GPIOB
#define RCC_USART					RCC_APB1Periph_USART3
#define PORT						GPIOB
#define TX							GPIO_Pin_10
#define RX							GPIO_Pin_11

/**
 * @brief Initialize USART on the APB bus.
 */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_initStructure;
	USART_InitTypeDef USART_initStructure;
	
	/* Configura the RCC clock */
	RCC_APB2PeriphClockCmd(RCC_PORT,ENABLE);
	
	#ifdef USE_USART1
		RCC_APB2PeriphClockCmd(RCC_USART,ENABLE);
	#else
		RCC_APB1PeriphClockCmd(RCC_USART,ENABLE);
	#endif
	
	/* Configure the GPIOs */
	GPIO_initStructure.GPIO_Pin = TX;
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_AF_PP;		
	GPIO_initStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT,&GPIO_initStructure);
	
	GPIO_initStructure.GPIO_Pin = RX;
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_Init(PORT,&GPIO_initStructure);
	
	/* Configure the USART peripheral */
	USART_initStructure.USART_BaudRate = 115200;
	USART_initStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_initStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_initStructure.USART_Parity = USART_Parity_No;
	USART_initStructure.USART_StopBits = USART_StopBits_1;
	USART_initStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART,&USART_initStructure);
	
	USART_Cmd(USART,ENABLE);
	
}	

/**
 * @brief printf redirection.
 */
int fputc(int ch,FILE *f)
{
	USART_SendData(USART,(u8)ch);
	while(USART_GetFlagStatus(USART,USART_FLAG_TXE)==RESET);
	return ch;
}



