#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stm32f10x.h"
#include "mpu_dmp_useapi.h"
#include "i2c_moni.h"

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "ANO_DT.h"

/* Data requested by client. */
#define PRINT_ACCEL     (0x01)			
#define PRINT_GYRO      (0x02)			
#define PRINT_QUAT      (0x04)			

#define ACCEL_ON        (0x01)			
#define GYRO_ON         (0x02)			

#define MOTION          (0)				
#define NO_MOTION       (1)				

/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (100)			

#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)


//MPU
struct rx_s {
    unsigned char header[3];			
    unsigned char cmd;					
};

//inv_mpu.cchip_cfg_s
struct hal_s {
    unsigned char sensors;				
    unsigned char dmp_on;				
    unsigned char wait_for_tap;			
    volatile unsigned char new_gyro;	
    unsigned short report;				
    unsigned short dmp_features;		
    unsigned char motion_int_mode;		
    struct rx_s rx;						
};
struct hal_s hal = {0};					//hal0

/* USB RX binary semaphore. Actually, it's just a flag. Not included in struct
 * because it's declared extern elsewhere.
 */
volatile unsigned char rx_new;			//

/* 
	The sensors can be mounted onto the board in any orientation. The mounting
 * matrix seen below tells the MPL how to rotate the raw data from thei
 * driver(s).
 * TODO: The following matrices refer to the configuration on an internal test
 * board at Invensense. If needed, please modify the matrices to match the
 * chip-to-body matrix for your particular set up.
 */
signed char gyro_orientation[9] = {-1, 0, 0,
                                    0,-1, 0,
                                    0, 0, 1 };

									

/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;

    return scalar;
}

///*/
//	Handle sensor on/off combinations. */
//static void setup_gyro(void)
//{
//    unsigned char mask = 0;
//    if (hal.sensors & ACCEL_ON)
//        mask |= INV_XYZ_ACCEL;
//    if (hal.sensors & GYRO_ON)
//        mask |= INV_XYZ_GYRO;
//    /* If you need a power transition, this function should be called with a
//     * mask of the sensors still enabled. The driver turns off any sensors
//     * excluded from this mask.
//     */
//    mpu_set_sensors(mask);
//    if (!hal.dmp_on)
//        mpu_configure_fifo(mask);
//}

//
//static void tap_cb(unsigned char direction, unsigned char count)
//{
//    char data[2];
//    data[0] = (char)direction;
//    data[1] = (char)count;
//    send_packet(PACKET_TYPE_TAP, data);
//}


//
//static void android_orient_cb(unsigned char orientation)
//{
//    send_packet(PACKET_TYPE_ANDROID_ORIENT, &orientation);
//}



void run_self_test(void)
{
    int result;
//    char test_packet[4] = {0};
    long gyro[3], accel[3];

	//
    result = mpu_run_self_test(gyro, accel);
	
	//result0x03,result0x07
    if (result == 0x3) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);				
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);				
		
        mpu_get_accel_sens(&accel_sens);		
//		accel_sens = 0;						
		accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);			
    }

}


void gyro_data_ready_cb(void)
{
    hal.new_gyro = 1;
}




void SYSTEM_Reset(void)
{
	__set_FAULTMASK(1);			
	NVIC_SystemReset();			
}



u8 mpu_dmp_init(void)
{
	int result;
	
	//MPU
    result = mpu_init();					
    
	//mpu
	if (result){
		SYSTEM_Reset();
		return 1;
	}

    /* If you're not using an MPU9150 AND you're not using DMP features, this
     * function will place all slaves on the primary bus.
     * mpu_set_bypass(1);
     */

    /* Get/set hardware configuration. Start gyro. */
    /* Wake up all sensors. */
    if(mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))			//
		return 2;
    /* Push both gyro and accel data into the FIFO. */
    if(mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))		//FIFO
		return 3;
    if(mpu_set_sample_rate(DEFAULT_MPU_HZ))						//MPU100HzDMPMPUDMPDMP
		return 4;
	
//    /* Read back configuration in case it was set improperly. */
//    mpu_get_sample_rate(&gyro_rate);
//    mpu_get_gyro_fsr(&gyro_fsr);
//    mpu_get_accel_fsr(&accel_fsr);

    /* Initialize HAL state variables. */
    memset(&hal, 0, sizeof(hal));
    hal.sensors = ACCEL_ON | GYRO_ON;							//
//    hal.report = PRINT_QUAT;									

    /* To initialize the DMP:
     * 1. Call dmp_load_motion_driver_firmware(). This pushes the DMP image in
     *    inv_mpu_dmp_motion_driver.h into the MPU memory.
     * 2. Push the gyro and accel orientation matrix to the DMP.
     * 3. Register gesture callbacks. Don't worry, these callbacks won't be
     *    executed unless the corresponding feature is enabled.
     * 4. Call dmp_enable_feature(mask) to enable different features.
     * 5. Call dmp_set_fifo_rate(freq) to select a DMP output rate.
     * 6. Call any feature-specific control functions.
     *
     * To enable the DMP, just call mpu_set_dmp_state(1). This function can
     * be called repeatedly to enable and disable the DMP at runtime.
     *
     * The following is a short summary of the features supported in the DMP
     * image provided in inv_mpu_dmp_motion_driver.c:
     * DMP_FEATURE_LP_QUAT: Generate a gyro-only quaternion on the DMP at
     * 200Hz. Integrating the gyro data at higher rates reduces numerical
     * errors (compared to integration on the MCU at a lower sampling rate).
     * DMP_FEATURE_6X_LP_QUAT: Generate a gyro/accel quaternion on the DMP at
     * 200Hz. Cannot be used in combination with DMP_FEATURE_LP_QUAT.
     * DMP_FEATURE_TAP: Detect taps along the X, Y, and Z axes.
     * DMP_FEATURE_ANDROID_ORIENT: Google's screen rotation algorithm. Triggers
     * an event at the four orientations where the screen should rotate.
     * DMP_FEATURE_GYRO_CAL: Calibrates the gyro data after eight seconds of
     * no motion.
     * DMP_FEATURE_SEND_RAW_ACCEL: Add raw accelerometer data to the FIFO.
     * DMP_FEATURE_SEND_RAW_GYRO: Add raw gyro data to the FIFO.
     * DMP_FEATURE_SEND_CAL_GYRO: Add calibrated gyro data to the FIFO. Cannot
     * be used in combination with DMP_FEATURE_SEND_RAW_GYRO.
     */
    if(dmp_load_motion_driver_firmware())											
		return 5;
    if(dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))		
		return 6;
//    dmp_register_tap_cb(tap_cb);													
//    dmp_register_android_orient_cb(android_orient_cb);							
    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |DMP_FEATURE_GYRO_CAL;
    if(dmp_enable_feature(hal.dmp_features))										
		return 7;
    if(dmp_set_fifo_rate(DEFAULT_MPU_HZ))											
		return 8;
	
    mpu_set_dmp_state(1);			
    hal.dmp_on = 1;					

	//
	run_self_test();
	
	return 0;
	
//    __enable_interrupt();
//    /* Wait for enumeration. */
//    while (USB_connectionState() != ST_ENUM_ACTIVE);
}


void SetReportFlag(u8 rawDataReportCmd,u8 quatDataReportCmd)
{
	if(rawDataReportCmd == SET){
		hal.report |= PRINT_GYRO;
		hal.report |= PRINT_ACCEL;
	}else{
		hal.report &= ~PRINT_GYRO;
		hal.report &= ~PRINT_ACCEL;
	}
	
	if(quatDataReportCmd == SET){
		hal.report |= PRINT_QUAT;
	}else{
		hal.report &= ~PRINT_QUAT;
	}
}


//dmp
#define q30  1073741824.0f					//q30
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;		//q30
unsigned long sensor_timestamp;				//
short gyro[3], accel[3], sensors;			//gyro[3], accel[3],sensorsFIFO
unsigned char more;							//FIFO
long quat[4];								//
float pit,rol,yaw;							//

u8 dmp_getdata(void)
{
	//
//	if (rx_new)
//		/* A byte has been received via USB. See handle_input for a list of
//		 * valid commands.
//		 */
//		handle_input();
//	msp430_get_clock_ms(&timestamp);

	//
//	if (hal.motion_int_mode) {
//		/* Enable motion interrupt. */
//		mpu_lp_motion_interrupt(500, 1, 5);				//
//		hal.new_gyro = 0;								//INT
	
//	/* Wait for the MPU interrupt. */
//		while (!hal.new_gyro)
//			__bis_SR_register(LPM0_bits + GIE);
//		/* Restore the previous sensor configuration. */
//		mpu_lp_motion_interrupt(0, 0, 0);
//		hal.motion_int_mode = 0;
//	}

	//DMP
//	if (!hal.sensors || !hal.new_gyro) {
//		/* Put the MSP430 to sleep until a timer interrupt or data ready
//		 * interrupt is detected.
//		 */
//		__bis_SR_register(LPM0_bits + GIE);
//		continue;
//	}

	//DMP
	if (hal.new_gyro && hal.dmp_on) {
		/* This function gets new data from the FIFO when the DMP is in
		 * use. The FIFO can contain any combination of gyro, accel,
		 * quaternion, and gesture data. The sensors parameter tells the
		 * caller which data fields were actually populated with new data.
		 * For example, if sensors == (INV_XYZ_GYRO | INV_WXYZ_QUAT), then
		 * the FIFO isn't being filled with accel data.
		 * The driver parses the gesture data to determine if a gesture
		 * event has occurred; on an event, the application will be notified
		 * via a callback (assuming that a callback function was properly
		 * registered). The more parameter is non-zero if there are
		 * leftover packets in the FIFO.
		 */
		if(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more)){		//FIFO
			return 1;
		}
		
		//FIFO,more
		if (!more)
			hal.new_gyro = 0;				
		
		/* Gyro and accel data are written to the FIFO by the DMP in chip
		 * frame and hardware units. This behavior is convenient because it
		 * keeps the gyro and accel outputs of dmp_read_fifo and
		 * mpu_read_fifo consistent.
		 *
		 *dmp_read_fifompu_read_fifoDMP
		 *mpu_read_fifoDMPdmp_read_fifoFIFO
		 */
//		if (sensors & INV_XYZ_GYRO && hal.report & PRINT_GYRO)						
//			send_packet(PACKET_TYPE_GYRO, gyro);
//		if (sensors & INV_XYZ_ACCEL && hal.report & PRINT_ACCEL)					
//			send_packet(PACKET_TYPE_ACCEL, accel);
		
		if(sensors & INV_XYZ_GYRO && hal.report & PRINT_GYRO   &&   sensors & INV_XYZ_ACCEL && hal.report & PRINT_ACCEL){
			ANO_DT_Send_Senser(accel[0],accel[1],accel[2],gyro[0],gyro[1],gyro[2],0,0,0,0);
		}


		/* Unlike gyro and accel, quaternions are written to the FIFO in
		 * the body frame, q30. The orientation is set by the scalar passed
		 * to dmp_set_orientation during initialization.
		 *
		 */
		if (sensors & INV_WXYZ_QUAT){					
//			send_packet(PACKET_TYPE_QUAT, quat);
			q0 = quat[0] / q30;
			q1 = quat[1] / q30;
			q2 = quat[2] / q30;
			q3 = quat[3] / q30;
			pit	= asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;
			rol = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; 
			yaw = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;
			
			//
			if(hal.report & PRINT_QUAT)
				ANO_DT_Send_Status(rol,pit,yaw,0,0,0);
		}
		
		//DMP0
		return 0;
		
	//DMP
	} else if (hal.new_gyro) {
		unsigned char sensors, more;
		/* This function gets new data from the FIFO. The FIFO can contain
		 * gyro, accel, both, or neither. The sensors parameter tells the
		 * caller which data fields were actually populated with new data.
		 * For example, if sensors == INV_XYZ_GYRO, then the FIFO isn't
		 * being filled with accel data. The more parameter is non-zero if
		 * there are leftover packets in the FIFO.
		 */
		if(mpu_read_fifo(gyro, accel, &sensor_timestamp, &sensors, &more)){				//FIFO
			//
			return 1;
		}
		if (!more)
			hal.new_gyro = 0;
//		if (sensors & INV_XYZ_GYRO && hal.report & PRINT_GYRO)
//			send_packet(PACKET_TYPE_GYRO, gyro);
//		if (sensors & INV_XYZ_ACCEL && hal.report & PRINT_ACCEL)
//			send_packet(PACKET_TYPE_ACCEL, accel);
		
		if(sensors & INV_XYZ_GYRO && hal.report & PRINT_GYRO   &&   sensors & INV_XYZ_ACCEL && hal.report & PRINT_ACCEL){
			ANO_DT_Send_Senser(accel[0],accel[1],accel[2],gyro[0],gyro[1],gyro[2],0,0,0,0);
		}
		return 0;
	}

	return 1;
}


