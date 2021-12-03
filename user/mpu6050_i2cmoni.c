
/**
* Interface with MPU6050 IMU through I2C
*/

#include "mpu6050_i2cmoni.h"
#include "i2c_moni.h"
#include "systick.h"

#define	SlaveAddress	0x68

/* MPU6050 Register Addresses */
#define	SMPLRT_DIV		0x19
#define	CONFIG				0x1A	
#define	GYRO_CONFIG		0x1B	
#define	ACCEL_CONFIG	0x1C	
#define FIFO_EN				0x23	
#define INT_PIN_CFG		0x37	
#define INT_ENABLE		0x38
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define USER_CTRL			0x6A	
#define	PWR_MGMT_1		0x6B	
#define PWR_MGMT_2		0x6C	
#define	WHO_AM_I			0x75	


/**
 * @brief Initialize the MPU6040 through I2C.
 */
void MPU6050_MoniI2c_Config(void)
{
	MoniI2c_WriteByteToSlave(SlaveAddress,PWR_MGMT_1, 0x80);			// Reset
	delay_ms(100);														
	MoniI2c_WriteByteToSlave(SlaveAddress,PWR_MGMT_1, 0x00);			// wakeup
	
	MoniI2c_WriteByteToSlave(SlaveAddress,GYRO_CONFIG, 0x18);			// gyroscope range
	MoniI2c_WriteByteToSlave(SlaveAddress,ACCEL_CONFIG, 0x00);		// accelerometer range
	MoniI2c_WriteByteToSlave(SlaveAddress,SMPLRT_DIV, 0x13);			// sampling rate scalar
	MoniI2c_WriteByteToSlave(SlaveAddress,CONFIG, 0x04);					// low-pass filter bandwidth
	MoniI2c_WriteByteToSlave(SlaveAddress,USER_CTRL, 0x00);				// fifo control
	MoniI2c_WriteByteToSlave(SlaveAddress,FIFO_EN, 0x00);					// fifo enable
	MoniI2c_WriteByteToSlave(SlaveAddress,INT_PIN_CFG, 0x80);			// interrupt configuration
	MoniI2c_WriteByteToSlave(SlaveAddress,INT_ENABLE, 0x00);			// disable interrupt
	
	MoniI2c_WriteByteToSlave(SlaveAddress,PWR_MGMT_1, 0x01);			// power management clock
	MoniI2c_WriteByteToSlave(SlaveAddress,PWR_MGMT_2, 0x00);			
}


/**
 * @brief Enable MPU6050 external interrupt.
 */
void MPU6050_MoniI2c_ITConfig(){
	MoniI2c_WriteByteToSlave(SlaveAddress,INT_PIN_CFG,0x01);
	MoniI2c_WriteByteToSlave(SlaveAddress,INT_ENABLE,0x01);
}


/**
 * @brief Get the ID for MPU6050.
 */
u8 MPU6050_MoniI2c_GetId(void)
{	
	u8 data;
	if(!MoniI2c_ReadFromSlave(SlaveAddress,0x75,&data)){
		return data;
	}else{
		return 0;
	}
}


/**
 * @brief Acquire x-axis accelerometer data.
 */
u16 MPU6050_MoniI2c_GetAccX(void)
{
	u8 tem[2];
	if(!MoniI2c_ReadSomeDataFromSlave(SlaveAddress,ACCEL_XOUT_H,2,tem)){
		return tem[0]<<8|tem[1];
	}else{
		return 0;
	}
}


/**
 * @brief Acquire y-axis accelerometer data.
 */
u16 MPU6050_MoniI2c_GetAccY(void)
{
	u8 tem[2];
	if(!MoniI2c_ReadSomeDataFromSlave(SlaveAddress,ACCEL_YOUT_H,2,tem)){
		return tem[0]<<8|tem[1];
	}else{
		return 0;
	}
}


/**
 * @brief Acquire z-axis accelerometer data.
 */
u16 MPU6050_MoniI2c_GetAccZ(void)
{
	u8 tem[2];
	if(!MoniI2c_ReadSomeDataFromSlave(SlaveAddress,ACCEL_ZOUT_H,2,tem)){
		return tem[0]<<8|tem[1];
	}else{
		return 0;
	}
}



/**
 * @brief Acquire x-axis gyroscope data.
 */
u16 MPU6050_MoniI2c_GetGyroX(void)
{
	u8 tem[2];
	if(!MoniI2c_ReadSomeDataFromSlave(SlaveAddress,GYRO_XOUT_H,2,tem)){
		return tem[0]<<8|tem[1];
	}else{
		return 0;
	}
}


/**
 * @brief Acquire y-axis gyroscope data.
 */
u16 MPU6050_MoniI2c_GetGyroY(void)
{
	u8 tem[2];
	if(!MoniI2c_ReadSomeDataFromSlave(SlaveAddress,GYRO_YOUT_H,2,tem)){
		return tem[0]<<8|tem[1];
	}else{
		return 0;
	}
}


/**
 * @brief Acquire z-axis gyroscope data.
 */
u16 MPU6050_MoniI2c_GetGyroZ(void)
{
	u8 tem[2];
	if(!MoniI2c_ReadSomeDataFromSlave(SlaveAddress,GYRO_ZOUT_H,2,tem)){
		return tem[0]<<8|tem[1];
	}else{
		return 0;
	}
}


/**
 * @brief Acquire temperature reading.
 */
float MPU6050_MoniI2c_GetTemperature(void)
{
	u8 tem[2];
	short value;		
	
	if(!MoniI2c_ReadSomeDataFromSlave(SlaveAddress,TEMP_OUT_H,2,tem)){
		value = (short)(tem[0]<<8|tem[1]);
		return (36.53+(value/ 340.0));
	}else{
		return 0;
	}
}


