/**
 * Hardware SPI interface.
 */

#include "spi.h"

#define CSN_LOW					GPIOB->BRR |= GPIO_Pin_1
#define CSN_HIGH				GPIOB->BSRR |= GPIO_Pin_1

u8 status;						

void SPI_Config(void)
{
	SPI_InitTypeDef   SPI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Configures the RCC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	/* Configues the GPIO */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	/* Configures the SPI peripheral */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;							
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;						
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					
	SPI_InitStructure.SPI_CRCPolynomial = 7;							
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
	
}


/**
 * @brief Read/Write through the SPI peripheral.
 * @param[in] Valid data to be sent to a slave.
 * @return Valid data received from the slave.
 */
u8 SPI_RW(u8 txData)
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI1,txData);
	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(SPI1);
}


/**
 * @brief Write a single byte thorough SPI.
 */
u8 SPI_Write_Byte(u8 reg, u8 value)
{
	CSN_LOW;			
	status = SPI_RW(reg);	
	SPI_RW(value);				
	CSN_HIGH;				
	
	return status;
}

/**
 * @brief Write continuous bytes through SPI.
 */
u8 SPI_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	CSN_LOW;

	status = SPI_RW(reg);
	while(len){
		SPI_RW(*pBuf);
		pBuf++;
		len--;
	}
	
	CSN_HIGH;
	
	return status;
}

/**
 * @brief Read a single byte through SPI.
 */
u8 SPI_Read_Byte(u8 reg)
{
	u8 value;
	CSN_LOW;
	SPI_RW(reg);
	value = SPI_RW(0);
	CSN_HIGH;
	
	return value;
}


/**
 * @brief Read continuous bytes through SPI.
 */
u8 SPI_Read_Buf(u8 reg, u8 *pBuf, u8 len)
{
	CSN_LOW;
	
	status = SPI_RW(reg);
	while(len){
		*pBuf = SPI_RW(0);
		pBuf++;
		len--;
	}

	CSN_HIGH;
	
	return status;
}


