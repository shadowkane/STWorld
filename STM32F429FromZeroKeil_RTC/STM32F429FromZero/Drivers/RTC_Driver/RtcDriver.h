#ifndef RTCDRIVER_H_
#define RTCDRIVER_H_

#include "stm32f4xx_hal.h"

#define DS3231_I2C_ADDRESS	0xD0 //0x68<<1 = 0xD0 to respect the MSB first obligation (Slave Address first 7 MSB then R/W bit "set automatically by the I2C library)

#define DS3231_REGISTER_ADDR_SECONDS					0x00
#define DS3231_REGISTER_ADDR_MINUTES					0x01
#define DS3231_REGISTER_ADDR_HOURS						0x02
#define DS3231_REGISTER_ADDR_DAY							0x03
#define DS3231_REGISTER_ADDR_DATE							0x04
#define DS3231_REGISTER_ADDR_MONTH_CENTURY		0x05
#define DS3231_REGISTER_ADDR_YEAR							0x06
#define DS3231_REGISTER_ADDR_ALARM1_SECONDS		0x07
#define DS3231_REGISTER_ADDR_ALARM1_MINUTES		0x08
#define DS3231_REGISTER_ADDR_ALARM1_HOURS			0x09
#define DS3231_REGISTER_ADDR_ALARM1_DAY_DATE	0x0A
#define DS3231_REGISTER_ADDR_ALARM2_MINUTES		0x0B
#define DS3231_REGISTER_ADDR_ALARM2_HOURS			0x0C
#define DS3231_REGISTER_ADDR_ALARM2_DAY_DATE	0x0D
#define DS3231_REGISTER_ADDR_CONTROL					0x0E
#define DS3231_REGISTER_ADDR_CONTROL_STATUS		0x0F
#define DS3231_REGISTER_ADDR_AGING_OFFSET			0x10
#define DS3231_REGISTER_ADDR_TEMPERATURE_MSB	0x11
#define DS3231_REGISTER_ADDR_TEMPERATURE_LSB	0x12


typedef struct _xRtcDateTime
{
	uint8_t u8Seconds;	//0-59
	uint8_t u8Minutes;	//0-59
	uint8_t u8Hours; 		//0-23
	uint8_t u8Days;			//1-7
	uint8_t u8Date;			//1-31
	uint8_t u8Month;		//1-12
	uint16_t u16Year;		
}t_xRtcDateTime;

typedef enum _enRtcInterruptionMode
{
	RtcInterruptionMode_SquareWave,
	RtcInterruptionMode_Alarm
}t_enRtcInterruptionMode;

typedef enum _enRtcAlarmRate
{
	// Alarm 1 mode
	enRtcAlarmRate_A1_PerSecond,
	enRtcAlarmRate_A1_MatchSecond,
	enRtcAlarmRate_A1_MatchSecondMinute,
	enRtcAlarmRate_A1_MatchSecondMinuteHours,
	enRtcAlarmRate_A1_MatchSecondMinuteHoursDate,
	enRtcAlarmRate_A1_MatchSecondMinuteHoursDay,
	// Alarm 2 mode
	enRtcAlarmRate_A2_PerMinute,
	enRtcAlarmRate_A2_MatchMinute,
	enRtcAlarmRate_A2_MatchMinuteHours,
	enRtcAlarmRate_A2_MatchMinuteHoursDate,
	enRtcAlarmRate_A2_MatchMinuteHoursDay
}t_enRtcAlarmRate;

void vRtcDriverConfig(I2C_HandleTypeDef* xRtcI2cHandler, uint8_t u8DeviceI2cAddress);
int iRtcSetInerruptionMode(t_enRtcInterruptionMode enInterruptionMode);
int iRtcEnableAlarm1();
int iRtcEnableAlarm2();
int iRtcDisableAlarm1();
int iRtcDisableAlarm2();
int iRtcClearAlarm1InteeruptionFlag();
int iRtcClearAlarm2InteeruptionFlag();
int iRtcSetSeconds(uint8_t u8Seconds);
int iRtcGetSeconds(uint8_t* pu8Seconds);
int iRtcSetDateTime(t_xRtcDateTime xDateTime);
int iRtcGetCurrentDateTime(t_xRtcDateTime* xCurrentDateTimeOut);
int iRtcSetAlarm(t_enRtcAlarmRate enAlarmRate, t_xRtcDateTime* xAlarm1DateTime);

#endif //RTCDRIVER_H_