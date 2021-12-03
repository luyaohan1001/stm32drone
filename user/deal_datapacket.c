/**
 * Packets data for nRF wireless transmission.
 */
#include "deal_datapacket.h"
#include "usart.h"

u8 dataPID;									
u8 buttonFlag = 0x00;								
vu16 remoteControl[4];								

extern u8 RxBuf[12];									


/**
 * @brief Unpack data from nRF
 * Header - KeyMak - ADC1 - ADC1 - ADC2 - ADC2 - ADC3 - ADC3 - ADC4 - ADC4 - PID - CRC
 */
void UnpackData(void)
{
	if(RxBuf[11]!=0xa5)							
		return;
	if(RxBuf[0] & 0x01){								
		remoteControl[0] = RxBuf[3]<<8|RxBuf[2];		//ADC2
		remoteControl[1] = RxBuf[5]<<8|RxBuf[4];		//ADC1
		remoteControl[2] = RxBuf[7]<<8|RxBuf[6];		//ADC4
		remoteControl[3] = RxBuf[9]<<8|RxBuf[8];		//ADC3
	}else if(RxBuf[0] & 0x08){							
		buttonFlag = RxBuf[1];
	}
	dataPID = RxBuf[10];
}







