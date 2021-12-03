/**
 * PID Control Algorithm.
 */
#include "control.h"
#include "mpu_dmp_useapi.h"
#include "motor_pwm.h"
#include "usart.h"


#define GYRO_COEFFICIENT		(2000.0/65535.0)		

/** Global Variables */
volatile float pitch_setpoint = 0.0;	
volatile float rol_setpoint = 0.0;		
volatile float yaw_setpoint.g;		

vs16 gyro_X,gyro_Y;						

vs16 motor_pwm[4];						

volatile float angular_speed_X = 0;		
volatile float angular_speed_Y = 0;		
vs16 pwm_X,pwm_Y;						
float e_I_Y,e_I_X;						
vs16 pwm_Yaw;							

extern float pit,rol,yaw;				
extern vu16 remoteControl[4];			
extern u8 buttonFlag;					


/**
 * @brief Interrupt handler for the MPU6050 IMU external interrupt.
 */
void EXTI15_10_IRQHandler(void)
{
	gyro_data_ready_cb();
	Get_Angle();

	Direction_Control();
	Outter_PID();
	Inner_PID();
	Rotation_Correction();
	
	DealPwm();
	Set_Pwm();
	
	EXTI_ClearFlag(EXTI_Line15);
}


/**
 * @brief Update the gyro angle.
 */
void Get_Angle(void)
{
	dmp_getdata();
	
	gyro_X = gyro[0]*GYRO_COEFFICIENT;
	gyro_Y = gyro[1]*GYRO_COEFFICIENT;
}


/**
 * @brief Update the set point of pitch and rol.
 */
void Direction_Control(void)
{
	pitch_setpoint = -(remoteControl[2]-15);
	
	rol_setpoint = remoteControl[3]-15;
}


/**
 * @brief Outer pid control.
 */
void Outter_PID(void)
{
	static float kp1=2;								
	static float kp2=1;							
	static float e_pit,e_rol;						
	
	e_pit = pitch_setpoint-pit;
	e_rol = rol_setpoint-rol;

	angular_speed_Y = kp2*e_pit;
	angular_speed_X = kp1*e_rol;
}


/**
 * @brief Inner pid control.
 */
void Inner_PID(void)
{
	static float kp1=30,ki1=0.5,kd1=30;				
	static float kp2=25,ki2=0.5,kd2=22;			
	static float e_X[2],e_Y[2];					
	static u8 flag_Y=0,flag_X=0;					
	
	e_Y[0] = angular_speed_Y - gyro_Y;
	e_X[0] = angular_speed_X - gyro_X;			

	/* Y-axis inner-loop PID */
	if(e_Y[0]>=150.0||e_Y[0]<=-150.0){
		flag_Y = 0;
	}else{
		flag_Y = 1;
		e_I_Y += e_Y[0];
	}
	
	/* Saturates the integral control. */
	if(e_I_Y>1000)
		e_I_Y=1000;
	if(e_I_Y<-1000)
		e_I_Y=-1000;
	
	/* New Y-axis output throttle */
	pwm_Y = kp2*e_Y[0]+flag_Y*ki2*e_I_Y+kd2*(e_Y[0]-e_Y[1]);
	
	
	/* X-axis inner-loop PID */
	if(e_X[0]>=150.0||e_X[0]<=150.0){
		flag_X = 0;
	}else{
		flag_X = 1;
		e_I_X += e_X[0];
	}
	
	/* Saturates the integral control. */
	if(e_I_X>1000)
		e_I_X=1000;             					
	if(e_I_X<-1000)	
		e_I_X=-1000;              					
	
	/* New X-axis output throttle */
	pwm_X = kp1*e_X[0]+flag_X*ki1*e_I_X+kd1*(e_X[0]-e_X[1]);
	
	/* Updates the error for next iteration */
	e_Y[1] = e_Y[0];								
	e_X[1] = e_X[0];								
	
}


/**
 * @brief Posture Correction
 */
void Rotation_Correction(void)
{
	static float kp1=40,kd1=60;						
	static float e_Yaw[2];							
	
	e_Yaw[0] = yaw_setpoint.g - yaw;

	/* New Z-axis output throttle. */
	pwm_Yaw = kp1*e_Yaw[0]+kd1*(e_Yaw[0]-e_Yaw[1]);
	
	e_Yaw[1] = e_Yaw[0];							
}


/**
 * @brief Configure PWM output based PID controller.
 */
void DealPwm(void)
{
	/* Initialize PID when drone is just powered. */
	if(!(buttonFlag & 0x01)){							

		angular_speed_Y = 0;
		angular_speed_X = 0;
		yaw_setpoint.g = yaw;
		
		pwm_X = 0;
		pwm_Y = 0;
		pwm_Yaw = 0;
		e_I_X = 0;
		e_I_Y = 0;
		
		remoteControl[1] = 1;
		return;
	}
	
	/* Enforce smooth throttle when it is small. */
	if(remoteControl[1]<=100){
		angular_speed_Y = 0;
		angular_speed_X = 0;
		yaw_setpoint.g = yaw;
		
		pwm_X = 0;
		pwm_Y = 0;
		pwm_Yaw = 0;
		e_I_X = 0;
		e_I_Y = 0;
	}
}


/**
 * Load correct PWM value to the motors.
 */
void Set_Pwm(void)
{
	static s16 max = 7150;
	static s16 min = 5;
	u8 i;
	
	/* Calculate the intended PWM value */
	motor_pwm[0] = remoteControl[1]+pwm_X-pwm_Y+pwm_Yaw;
	motor_pwm[1] = remoteControl[1]+pwm_X+pwm_Y-pwm_Yaw;
	motor_pwm[2] = remoteControl[1]-pwm_X+pwm_Y+pwm_Yaw;
	motor_pwm[3] = remoteControl[1]-pwm_X-pwm_Y-pwm_Yaw;
	
	/* Pervent setting too large of a PWM to a motor. */
	for(i=0;i<4;i++){
		if(motor_pwm[i] >= max){
			motor_pwm[i] = max;
		}else if(motor_pwm[i] <= min){
			motor_pwm[i] = 1;
		}
	}
	
	motor1_SetPulse(motor_pwm[0]);
	motor2_SetPulse(motor_pwm[1]);
	motor3_SetPulse(motor_pwm[2]);
	motor4_SetPulse(motor_pwm[3]);
}

