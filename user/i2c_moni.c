#include "i2c_moni.h"
#include "systick.h"

#define I2C_PORT 				GPIOB
#define I2C_SCL 				GPIO_Pin_6
#define I2C_SDA 				GPIO_Pin_7
#define RCC_I2C_PORT 			RCC_APB2Periph_GPIOB

#define I2C_SCL_LOW 			(I2C_PORT->BRR |= I2C_SCL)
#define I2C_SCL_HIGH 			(I2C_PORT->BSRR |= I2C_SCL)
#define I2C_SDA_LOW 			(I2C_PORT->BRR |= I2C_SDA)
#define I2C_SDA_HIGH 			(I2C_PORT->BSRR |= I2C_SDA)

#define I2C_SDA_READ 			(I2C_PORT->IDR & I2C_SDA)


/**
 * @brief I2C initialization.
 */
void I2C_MoniConfig(void){
	GPIO_InitTypeDef GPIO_initStruct;
	
	RCC_APB2PeriphClockCmd(RCC_I2C_PORT,ENABLE);
	
	GPIO_initStruct.GPIO_Pin = I2C_SCL|I2C_SDA;
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_Out_OD;		
	GPIO_initStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(I2C_PORT,&GPIO_initStruct);
	
	I2C_SCL_LOW;
	delay_us(1);
	I2C_SDA_HIGH;
	delay_us(1);
}


/**
 * @brief Check if I2C bus is busy.
 */
void _I2C_IsBusy(void)
{
	while(!I2C_SDA_READ){
		
		I2C_SCL_LOW;
		delay_us(3);
		I2C_SCL_HIGH;
		delay_us(3);
	}
}	


/**
 * @brief I2C Start signaling.
 */
void I2C_Start(void){
	_I2C_IsBusy();
	I2C_SCL_LOW;
	delay_us(1);
	
	I2C_SDA_HIGH;
	delay_us(1);
	I2C_SCL_HIGH;
	delay_us(1);
	I2C_SDA_LOW;
	delay_us(1);
	
	I2C_SCL_LOW;
	delay_us(1);
}


/**
 * @brief Stop signal.
 */
void I2C_Stop(void){
	I2C_SCL_LOW;
	delay_us(1);
	
	I2C_SDA_LOW;
	delay_us(1);
	I2C_SCL_HIGH;
	delay_us(1);
	I2C_SDA_HIGH;
	delay_us(1);
	
}


/**
 * @brief Set acknowledge.
 */
void I2C_SetAck(FunctionalState ackState){
	I2C_SCL_LOW;
	delay_us(1);
	
	if(ackState == ENABLE){
		I2C_SDA_LOW;
		delay_us(1);
	}else{
		I2C_SDA_HIGH;
		delay_us(1);
	}
	
	I2C_SCL_HIGH;
	delay_us(2);
	
	I2C_SCL_LOW;
	delay_us(1);
	
	I2C_SDA_HIGH;
	delay_us(1);
}


/**
 * @brief Check acknowledge.
 */
FunctionalState I2C_GetAck(void){
	FunctionalState ask;
	
	I2C_SCL_HIGH;
	delay_us(1);
	
	if(I2C_SDA_READ){
		ask = DISABLE;
	}else{
		ask = ENABLE;
	}
	
	I2C_SCL_LOW;
	delay_us(1);
	
	return ask;
}


/**
 * @brief Write one byte to the I2C bus.
 */
FunctionalState MoniI2C_WriteByte(u8 data){
	u8 i;
	
	for(i=0;i<8;i++){
		I2C_SCL_LOW;
		delay_us(1);
		
		if(data & 0x80){
			I2C_SDA_HIGH;
		}else{
			I2C_SDA_LOW;
		}
		data <<=1;
		delay_us(1);
		
		I2C_SCL_HIGH;
		delay_us(2);
	}
	
	I2C_SCL_LOW;
	delay_us(1);
	I2C_SDA_HIGH;
	delay_us(1);
	
	return I2C_GetAck();
}


/**
 * @brief Read one byte from the I2C bus.
 */
u8 MoniI2C_ReadByte(FunctionalState ackState){
	u8 i;
	u8 data = 0x00;
	
	for(i=0;i<8;i++){
		I2C_SCL_HIGH;
		delay_us(1);
		
		data <<=1;
		if(I2C_SDA_READ){
			data |= 0x01;
		}
		
		I2C_SCL_LOW;
		delay_us(2);
	}
	
	I2C_SetAck(ackState);
	
	return data;
}


/**
 * @brief Write a single byte to the slave.
 */
u8 MoniI2c_WriteByteToSlave(u8 addr,u8 reg,u8 data)
{
	FunctionalState state;					
	                                                
	I2C_Start();                                  
	state = MoniI2C_WriteByte(addr<<1|0);          
	if(state == ENABLE){                           
		state = MoniI2C_WriteByte(reg);     		
		if(state == ENABLE){                        
			MoniI2C_WriteByte(data);                
			
			I2C_Stop();
			return 0;
		}
	}

	I2C_Stop();
	return 1;
}                                                  


/**
 * @brief Write continuous bytes to the slave.
 */
u8 MoniI2c_WriteSomeDataToSlave(u8 addr,u8 reg,u8 len,u8 *buf)
{
	FunctionalState state;					
	u8 i;
	
	I2C_Start();                                    
	state = MoniI2C_WriteByte(addr<<1|0);            
	if(state == ENABLE){                           
		state = MoniI2C_WriteByte(reg);      			
		if(state == ENABLE){
			for(i=0;i<len;i++){							
				state = MoniI2C_WriteByte(*(buf+i));    
				if(state == DISABLE){				
					I2C_Stop();                       
					return 1;
				}
			}
			
			I2C_Stop();                                      	
			return 0;
		}                                          
	}                              
	
	I2C_Stop();
	return 1;
}                                                  


u8 MoniI2c_ReadFromSlave(u8 addr,u8 reg,u8 *buf)
{
	FunctionalState state;
	
	I2C_Start();
	state = MoniI2C_WriteByte(addr<<1|0);		
	if(state == ENABLE){
		state = MoniI2C_WriteByte(reg);				
		if(state == ENABLE){
			I2C_Start();							
			state = MoniI2C_WriteByte(addr<<1|1);	
			if(state == ENABLE){
				*buf = MoniI2C_ReadByte(DISABLE);	
				
				I2C_Stop();
				return 0;
			}
		}
	}
	
	I2C_Stop();
	return 1;	
}


u8 MoniI2c_ReadSomeDataFromSlave(u8 addr,u8 reg,u8 len,u8 *buf)
{
	FunctionalState state;
	
	I2C_Start();
	state = MoniI2C_WriteByte(addr<<1|0);						
	if(state == ENABLE){
		state = MoniI2C_WriteByte(reg);								
		if(state == ENABLE){
			I2C_Start();
			state = MoniI2C_WriteByte(addr<<1|1);					
			if(state == ENABLE){
				while(len){
					if(len==1){										
						*buf = MoniI2C_ReadByte(DISABLE);		
					}else{
						*buf = MoniI2C_ReadByte(ENABLE);		
					}
					len--;
					buf++;
				}
				I2C_Stop();
				return 0;
			}
		}
	}
	
	I2C_Stop();
	return 1;
}

