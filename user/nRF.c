/**
 * This file is a library for interfacing the nRF24L01 wireless transciever.
 */

#include "nRF.h"
#include "spi.h"
#include "systick.h"
#include "usart.h"
#include "led.h"
#include "deal_datapacket.h"

#define CE_LOW					GPIOA->BRR |= GPIO_Pin_4
#define CE_HIGH					GPIOA->BSRR |= GPIO_Pin_4


/* NRF24L01 */
#define TX_ADR_WIDTH    		5   		
#define RX_ADR_WIDTH    		5   		
#define TX_PLOAD_WIDTH  		11  		
#define RX_PLOAD_WIDTH  		12  		
#define READ_REG_CMD        	0x00  		
#define WRITE_REG_CMD       	0x20 		
#define RD_RX_PLOAD     		0x61  		
#define WR_TX_PLOAD     		0xA0  		
#define FLUSH_TX        		0xE1 		
#define FLUSH_RX        		0xE2  	
#define REUSE_TX_PL     		0xE3  		
#define NOP            			0xFF  
/* SPI Peripheral */		
#define CONFIG          		0x00  		
#define EN_AA           		0x01  		
#define EN_RXADDR       		0x02  		
#define SETUP_AW        		0x03  		
#define SETUP_RETR      		0x04  		
#define RF_CH           		0x05  		
#define RF_SETUP        		0x06  		
#define STATUS          		0x07  		
#define OBSERVE_TX      		0x08  		
#define CD              		0x09  		
#define RX_ADDR_P0      		0x0A  		
#define RX_ADDR_P1      		0x0B  		
#define RX_ADDR_P2      		0x0C  		
#define RX_ADDR_P3      		0x0D  		
#define RX_ADDR_P4      		0x0E  		
#define RX_ADDR_P5      		0x0F  		
#define TX_ADDR         		0x10  		
#define RX_PW_P0        		0x11 		
#define RX_PW_P1        		0x12  		
#define RX_PW_P2        		0x13  		
#define RX_PW_P3        		0x14  		
#define RX_PW_P4        		0x15  		
#define RX_PW_P5        		0x16  		
#define FIFO_STATUS     		0x17  		

/* nRF24 effective TX and RX addreses. */
u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};	
u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};	

/* IRQ source*/
#define TX_DS					0x20		
#define RX_DR					0x40		
#define MAX_RT					0x10		

/* Global Variables. */
vu8 sta;									
u8 RxBuf[RX_PLOAD_WIDTH];					

extern u8 buttonFlag;						

/**
 * @brief Initialize NRF module and the external interrupt.
 */
void NRF_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructus;
	EXTI_InitTypeDef EXTI_initStructure;
	
	SPI_Config();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructus.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructus.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructus.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructus);

	GPIO_InitStructus.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructus.GPIO_Mode = GPIO_Mode_IPU;						
	GPIO_Init(GPIOB,&GPIO_InitStructus);

	EXTI_initStructure.EXTI_Line = EXTI_Line0;
	EXTI_initStructure.EXTI_LineCmd = ENABLE;
	EXTI_initStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_initStructure.EXTI_Trigger = EXTI_Trigger_Falling;				
	EXTI_Init(&EXTI_initStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);				
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	
	CE_LOW;																
	
	/* Initialize nRF */
	SPI_Write_Byte(WRITE_REG_CMD + SETUP_AW, 0x03);							// default comm address width.
	SPI_Write_Buf(WRITE_REG_CMD + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    	
	SPI_Write_Buf(WRITE_REG_CMD + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); 	// RX address
	SPI_Write_Byte(WRITE_REG_CMD + SETUP_RETR, 0x1a); 						// Re-entry delay 
	SPI_Write_Byte(WRITE_REG_CMD + EN_AA, 0x01);      						// Channel 0 reponse trigger
	SPI_Write_Byte(WRITE_REG_CMD + EN_RXADDR, 0x01);  						// Channel 0
	
	SPI_Write_Byte(WRITE_REG_CMD + RF_SETUP, 0x07);   						// TX rate 1 MHz, 0dB 
	SPI_Write_Byte(WRITE_REG_CMD + RF_CH, 30);        						// TX Freq
	SPI_Write_Byte(WRITE_REG_CMD + RX_PW_P0, RX_PLOAD_WIDTH); 				// RX data width.

	SPI_Write_Byte(WRITE_REG_CMD + CONFIG, 0x0f);   						// RX mode.

	/* Check if the configurations are correct */
	//	printf("SETUP_AW:%x\r\n",SPI_Read_Byte(READ_REG_CMD+SETUP_AW));
	//	printf("SETUP_RETR:%x\r\n",SPI_Read_Byte(READ_REG_CMD+SETUP_RETR));
	//	printf("EN_RXADDR:%x\r\n",SPI_Read_Byte(READ_REG_CMD+EN_RXADDR));
	//	printf("EN_AA:%x\r\n",SPI_Read_Byte(READ_REG_CMD+EN_AA));
	//	printf("RF_SETUP:%x\r\n",SPI_Read_Byte(READ_REG_CMD+RF_SETUP));
	//	printf("RF_CH:%x\r\n",SPI_Read_Byte(READ_REG_CMD+RF_CH));
	//	printf("RX_PW_P0:%x\r\n",SPI_Read_Byte(READ_REG_CMD+RX_PW_P0));
	//	printf("CONFIG:%x\r\n",SPI_Read_Byte(READ_REG_CMD+CONFIG));

	CE_HIGH;
}

/**
 * @brief Interrupt handler for the nRF module external interrupt.
 */
void EXTI0_IRQHandler(void)
{
	CE_LOW;													
	sta = SPI_Read_Byte(READ_REG_CMD+STATUS);				
	/* Switch to RX Mode after transmission. */
	if(sta & TX_DS){										
		RX_Mode();											
	}else if(sta & RX_DR){	
		/* Receive remote control packets.*/								
		NRF_ReceivePacket();							
		if(buttonFlag & 0x01){
			LED_On(LED9);									
		}else{
			LED_Toggle(LED9);								
		}
	}else if(sta & MAX_RT){									
		RX_Mode();											
		SPI_Write_Byte(WRITE_REG_CMD+STATUS,sta);			
	}
	
	EXTI_ClearITPendingBit(EXTI_Line0);
}



/**
 * @brief Initialize the module to RX mode.
 */
void RX_Mode(void)
{
	CE_LOW;													
	SPI_Write_Byte(WRITE_REG_CMD + CONFIG, 0x0f); 			// RX mode
	SPI_Write_Byte(WRITE_REG_CMD + STATUS, 0x7e);			// Clear interrupt flag
	CE_HIGH; 											
}


/**
 * @brief Reads received data in local nRF.
 */
void NRF_ReceivePacket(void)
{
	CE_LOW;
	
	SPI_Read_Buf(RD_RX_PLOAD,RxBuf,RX_PLOAD_WIDTH);			// Read data from RX FIFO
	SPI_Write_Byte(WRITE_REG_CMD+STATUS,sta);   			// Clear interrupt flag.
	
	UnpackData();											
	
	CE_HIGH;												
}


/**
 * @brief Sends continuous bytes to nRF by writing to the TX BUFFER.
 */
void NRF_SendPacket(u8* tfbuf)
{
	CE_LOW;																	
	
	SPI_Write_Buf(WR_TX_PLOAD, tfbuf, TX_PLOAD_WIDTH); 						
	
	SPI_Write_Byte(WRITE_REG_CMD + CONFIG, 0x0e); 							// TX Mode
	SPI_Write_Byte(WRITE_REG_CMD + STATUS, 0x7e);							// Clear interrupt flag.
	
	CE_HIGH;																
	
	delay_ms(1);															
}





