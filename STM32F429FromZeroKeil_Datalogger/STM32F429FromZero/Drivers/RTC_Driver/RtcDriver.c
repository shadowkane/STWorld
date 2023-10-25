#include "RtcDriver.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct _RtcDevice
{
	I2C_HandleTypeDef* xRtcI2cHandler;
	uint8_t u8Address;
}t_RtcDevice;


static t_RtcDevice xRtcDevice;

static int iRtc_ReadByte(uint8_t u8Register, uint8_t* pu8DataOut);
static int iRtc_ReadNBytes(uint8_t u8Register, int iBufferSize, uint8_t* pu8BufferOut);
static int iRtc_WriteByte(uint8_t u8Register, uint8_t u8DataIn);
static int iRtc_WriteNBytes(uint8_t u8Register, uint8_t* pu8BufferIn, int iBufferSize);
static uint8_t u8Ds3231SecondsDecoder(uint8_t u8RawData);
static uint8_t u8Ds3231SecondsCoder(uint8_t u8Seconds);
static uint8_t u8Ds3231MinutesDecoder(uint8_t u8RawData);
static uint8_t u8Ds3231MinutesCoder(uint8_t u8Minutes);
static void vDs3231HoursDecoder(uint8_t u8RawData, uint8_t* u8HoursOut, bool* bIs24HourFromatOut, bool* bIsAmOut);
static uint8_t u8Ds3231HoursCoder(uint8_t u8Hours, bool bIs24HourFormat, bool bIsAm);
static uint8_t u8Ds3231Hours24FormatDecoder(uint8_t u8RawData);
static uint8_t u8Ds3231Hours24FormatCoder(uint8_t u8Hours);
static uint8_t u8Ds3231DateDecoder(uint8_t u8RawData);
static uint8_t u8Ds3231DateCoder(uint8_t u8Date);
static uint8_t u8Ds3231MonthDecoder(uint8_t u8RawData);
static uint8_t u8Ds3231MonthCoder(uint8_t u8Month);
static uint16_t u16Ds3231YearDecoder(uint8_t u8RawData);
static uint8_t u8Ds3231YearCoder(uint16_t u16Year);
		
// read 1 byte from register
// parameters: u8Register(register to read from), pu8DataOut(pointer to store data)
// returns: read results if succ return 0 otherwise return error value (-1:failure)
static int iRtc_ReadByte(uint8_t u8Register, uint8_t* pu8DataOut)
{
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	printf("iRtc_ReadByte:\r\n");
	#endif
	int iErrVal = 0;

	// alternative method to read from I2C device
//	iErrVal = HAL_I2C_Master_Transmit(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, &u8Register, 1, HAL_MAX_DELAY);
//	if(iErrVal != HAL_OK)
//	{
//		printf("iRtc_ReadByte HAL_I2C_Master_Transmit succ\r\n");
//		iErrVal = HAL_I2C_Master_Receive(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, pu8DataOut, 1, HAL_MAX_DELAY);
//	}
	
	iErrVal = HAL_I2C_Mem_Read(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, u8Register, I2C_MEMADD_SIZE_8BIT, pu8DataOut, 1, HAL_MAX_DELAY);
	if(iErrVal != HAL_OK)
	{
		#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
		printf("	iRtc_ReadByte failed(0x%02X), err:%d\r\n", u8Register, iErrVal);
		#endif
		iErrVal = -1;
	}
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	else
	{
		printf("	iRtc_ReadByte succ read (0x%02X=>0x%02X)\r\n", u8Register, *pu8DataOut);
	}
	#endif
	return iErrVal;
}

// read n bytes start from register
// parameters: u8Register(register to start reading from), iBufferSize(how many bytes to read also it's buffer size,) pu8DataOut(buffer to store data)
// returns: read results if succ return 0 otherwise return error value (-1:failure)
static int iRtc_ReadNBytes(uint8_t u8Register, int iBufferSize, uint8_t* pu8BufferOut)
{
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	printf("iRtc_ReadNBytes\r\n");
	#endif
	int iErrVal = 0;
	int i;
	
	iErrVal = HAL_I2C_Mem_Read(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, u8Register, I2C_MEMADD_SIZE_8BIT, pu8BufferOut, iBufferSize, HAL_MAX_DELAY);
	if(iErrVal != HAL_OK)
	{
		#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
		printf("	iRtc_ReadNBytes failed(0x%02X), err:%d\r\n", u8Register, iErrVal);
		#endif
		iErrVal = -1;
	}
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	else
	{
		printf("	iRtc_ReadNBytes succ read (0x%02X => ", u8Register);
		for(i=0; i<iBufferSize; i++)
		{		
			printf(" 0x%02X", pu8BufferOut[i]);
		}
		printf(")\r\n");
	}
	#endif
	return iErrVal;
}

// write 1 byte in register
// parameters: u8Register(register to write in), u8DataIn(data to wrtie)
// returns: write results if succ return 0 otherwise return error value (-1:failure)
static int iRtc_WriteByte(uint8_t u8Register, uint8_t u8DataIn)
{
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	printf("iRtc_WriteByte:\r\n");
	#endif
	int iErrVal = 0;

// alternative method to write in I2C device
//	uint8_t bytes[2] = { u8Register, u8DataIn };
//	iErrVal = HAL_I2C_Master_Transmit(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, bytes, 2, HAL_MAX_DELAY);
	
	iErrVal = HAL_I2C_Mem_Write(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, u8Register, I2C_MEMADD_SIZE_8BIT, &u8DataIn, 1, HAL_MAX_DELAY);
	if(iErrVal != HAL_OK)
	{
		#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
		printf("	iRtc_WriteByte failed(0x%02X), err:%d\r\n", u8Register, iErrVal);
		#endif
		iErrVal = -1;
	}
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	else
	{
		printf("	iRtc_WriteByte succ write(0x%02X=>0x%02X)\r\n", u8Register, u8DataIn);
	}
	#endif
	return iErrVal;
}

// write n bytes start from register
// parameters: u8Register(register to start the writing from), u8DataIn(data to wrtie), pu8BufferIn (buffer to write), iBufferSize (buffer size)
// returns: write results if succ return 0 otherwise return error value (-1:failure)
static int iRtc_WriteNBytes(uint8_t u8Register, uint8_t* pu8BufferIn, int iBufferSize)
{
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	printf("iRtc_WriteNBytes\r\n");
	#endif
	int iErrVal = 0;
	int i;
		
	iErrVal = HAL_I2C_Mem_Write(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, u8Register, I2C_MEMADD_SIZE_8BIT, pu8BufferIn, iBufferSize, HAL_MAX_DELAY);
	if(iErrVal != HAL_OK)
	{
		#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
		printf("	iRtc_WriteNBytes failed(0x%02X), err:%d\r\n", u8Register, iErrVal);
		#endif
		iErrVal = -1;
	}
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	else
	{
		printf("	iRtc_WriteNBytes succ write (0x%02X => ", u8Register);
		for(i=0; i<iBufferSize; i++)
		{		
			printf(" 0x%02X", pu8BufferIn[i]);
		}
		printf(")\r\n");
	}
	#endif
	return iErrVal;
}

// decode seconds from ds3231 seconds register to readable seconds
// parameters: u8RawData(seconds in raw form (from seconds register))
// returns: readable seconds in u8 type
static uint8_t u8Ds3231SecondsDecoder(uint8_t u8RawData)
{
	uint8_t seconds;
	
	// first 4 bits represend 0-9 seconds | second 4 bits represent 10 seconds 0-5
	seconds = (((u8RawData>>4)&0x0f)*10) + (u8RawData&0x0f);
	
	return seconds;
}

// code readable seconds to ds3231 seconds format
// parameters: u8Seconds(readable seconds in u8 type)
// returns: seconds in ds3231 format(u8 type)
static uint8_t u8Ds3231SecondsCoder(uint8_t u8Seconds)
{
	uint8_t u8Data;
	
	// first 4 bits represend 0-9 seconds | second 4 bits represent 10 seconds 0-5
	u8Data = (u8Seconds/10)<<4;
	u8Data |= u8Seconds%10;
	
	return u8Data;
}

// decode minutes from ds3231 minutes register to readable minutes
// parameters: u8RawData(minutes in raw form (from minutes register))
// returns: readable minutes in u8 type
static uint8_t u8Ds3231MinutesDecoder(uint8_t u8RawData)
{
	uint8_t minutes;
	
	// first 4 bits represend 0-9 seconds | second 4 bits represent 10 seconds 0-5
	minutes = (((u8RawData>>4)&0x0f)*10) + (u8RawData&0x0f);
	
	return minutes;
}

// code readable minutes to ds3231 minutes format
// parameters: u8Minutes(readable minutes in u8 type)
// returns: minutes in ds3231 format(u8 type)
static uint8_t u8Ds3231MinutesCoder(uint8_t u8Minutes)
{
	uint8_t u8Data;
	
	// first 4 bits represend 0-9 seconds | second 4 bits represent 10 seconds 0-5
	u8Data = (u8Minutes/10)<<4;
	u8Data |= u8Minutes%10;
	
	return u8Data;
}

// decode hours from ds3231 hours register to readable hours
// parameters: u8RawData(hours in raw form (from hours register)), u8HoursOut(output: readable hours in u8 type), bIs24HourFromatOut(output: true if 24-hour format, false if 12-hour format, bIsAmOut(output: usefull only for 12-hour format, true if AM, false if PM)
// returns: 
static void vDs3231HoursDecoder(uint8_t u8RawData, uint8_t* u8HoursOut, bool* bIs24HourFromatOut, bool* bIsAmOut)
{
	uint8_t hours;
	
	// bit 6 represent the hour format, 1:12-format | 0:24-format
	if(u8RawData&0x40)
	{
		// 12-hour format
		*bIs24HourFromatOut = false;
		// bit 5 for AM/PM (1:PM | 0:AM)
		if(u8RawData&0x20)
		{
			//PM
			*bIsAmOut = false;
		}
		else
		{
			//AM
			*bIsAmOut = true;
		}
		// bit 4 represent the tens place of hour
		*u8HoursOut = ((u8RawData&0x10)>>4)*10;
	}
	else
	{
		// 24-hour foramt
		*bIs24HourFromatOut = true;
		// bit 4-5 represent the tens place of hour
		*u8HoursOut = ((u8RawData&0x30)>>4)*10;
	}
		
	// first 4 bits represend ones place of hour
	*u8HoursOut |= (u8RawData&0x0f);

}

// code readable hours to ds3231 hours format
// parameters: u8Hours(readable hours in u8 type), bIs24HourFormat(set to true if 24-hour format is used), bIsAm(used only in 12-hour format and set it true if it's AM)
// returns: hours in ds3231 format(u8 type)
static uint8_t u8Ds3231HoursCoder(uint8_t u8Hours, bool bIs24HourFormat, bool bIsAm)
{
	uint8_t u8Data;
	
	// first 4 bits represend ones place
	u8Data = (u8Hours%10)&0x0f;
	if(bIs24HourFormat)
	{
		// bit 4-5 represent tens place in 24-hour format | bit 6 represent the hour format (24-hour format:0/12-hours format:1)
		// set bit 6 to 0 to enable the 24-hour format
		u8Data |= ((u8Hours/10)<<4)&0x30;
	}
	else
	{
		// in 12-hour format: bit 4 represent tens place | bit 5 represent AM:0/PM:1 | bit 6 represent the hour format (24-hour format:0/12-hours format:1)
		//u8Data |= ((u8Hours/10)<<4)&0x10;
		if(u8Hours>9)
		{
			u8Data |= 0x10;
		}
		// set bit 5 to 1 if it's PM otherwise leave it 0
		if(!bIsAm)
		{
				u8Data |= 0x20;
		}
		// set bit 6 to 1 to enable the 12-hour format
		u8Data |= 0x40;
	}
	
	return u8Data;
}


// decode hours from ds3231 hours register to readable hours in 24-hour format
// parameters: u8RawData(hours in raw form (from hours register))
// returns: readable hours in 24-hour format in u8 type
static uint8_t u8Ds3231Hours24FormatDecoder(uint8_t u8RawData)
{
	uint8_t hours;
	
	// bit 6 represent the hour format, 1:12-format | 0:24-format
	if(u8RawData&0x40)
	{
		// 12-hour format
		// bit 4 represent the tens place of hour
		hours = ((u8RawData&0x10)>>4)*10;
		// bit 5 for AM/PM (1:PM | 0:AM)
		if(u8RawData&0x20)
		{
			//PM
			hours += 12;
		}
	}
	else
	{
		// 24-hour foramt
		// bit 4-5 represent the tens place of hour
		hours = ((u8RawData&0x30)>>4)*10;
	}
	// first 4 bits represend ones place of hour
	hours |= (u8RawData&0x0f);

	return hours;
}

// code readable hours in 24-hour format to ds3231 hours format
// parameters: u8Hours(readable hours in 24-hour format in u8 type)
// returns: hours in ds3231 format in 24-hour format(u8 type)
static uint8_t u8Ds3231Hours24FormatCoder(uint8_t u8Hours)
{
	uint8_t u8Data;
	
	// first 4 bits represend ones place |  bits 4-5 represent tens place of hours with range of 0-23
	u8Data = ((u8Hours/10)<<4)&0x30;
	u8Data |= u8Hours%10;
	
	return u8Data;
}

// decode date from ds3231 date register to readable date
// parameters: u8RawData(date in raw form (from date register))
// returns: readable date in u8 type
static uint8_t u8Ds3231DateDecoder(uint8_t u8RawData)
{
	uint8_t date;
	
	// first 4 bits represend ones place |  bits 4-5 represent tens place of date with date range of 1-31
	date = (((u8RawData>>4)&0x03)*10) + (u8RawData&0x0f);
	
	return date;
}

// code readable date to ds3231 date format
// parameters: u8Date(readable date in u8 type)
// returns: date in ds3231 format(u8 type)
static uint8_t u8Ds3231DateCoder(uint8_t u8Date)
{
	uint8_t u8Data;
	
	// first 4 bits represend ones place |  bits 4-5 represent tens place of date with date range of 1-31
	u8Data = (u8Date/10)<<4;
	u8Data |= u8Date%10;
	
	return u8Data;
}

// decode month from ds3231 month register to readable month
// parameters: u8RawData(month in raw form (from month register))
// returns: readable month in u8 type
static uint8_t u8Ds3231MonthDecoder(uint8_t u8RawData)
{
	uint8_t month;
	
	// first 4 bits represend ones place | bits 4-5 represent tens place of month with a range of 1-12
	month = (((u8RawData>>4)&0x0f)*10) + (u8RawData&0x0f);
	
	return month;
}

// code readable month to ds3231 month format
// parameters: u8Month(readable month in u8 type)
// returns: month in ds3231 format(u8 type)
static uint8_t u8Ds3231MonthCoder(uint8_t u8Month)
{
	uint8_t u8Data;
	
	// first 4 bits represend ones place | bits 4-5 represent tens place of month with a range of 1-12
	u8Data = (u8Month/10)<<4;
	u8Data |= u8Month%10;
	
	return u8Data;
}

// decode year from ds3231 year register to readable year
// parameters: u8RawData(year in raw form (from year register))
// returns: readable year in u16 type
static uint16_t u16Ds3231YearDecoder(uint8_t u8RawData)
{
	uint16_t year;
	
	// first 4 bits represend ones place | second 4 bits represent tens place of year with a range of 00-99
	year = (((u8RawData>>4)&0x0f)*10) + (u8RawData&0x0f);
	// add 2000 since this is the year +2000
	year += 2000;
	return year;
}

// code readable year to ds3231 year format
// parameters: u16Year(readable year in u16 type)
// returns: year in ds3231 format(u8 type)
static uint8_t u8Ds3231YearCoder(uint16_t u16Year)
{
	uint8_t u8Data;
	
	// sub 2000 from year since RTC doesn't store this information
	u16Year -= 2000;
	// first 4 bits represend ones place | second 4 bits represent tens place of year with a range of 00-99
	u8Data = (u16Year/10)<<4;
	u8Data |= u16Year%10;

	return u8Data;
}



void vRtcDriverConfig(I2C_HandleTypeDef* xRtcI2cHandler, uint8_t u8DeviceI2cAddress)
{
	xRtcDevice.xRtcI2cHandler = xRtcI2cHandler;
	xRtcDevice.u8Address = u8DeviceI2cAddress;
}

int iRtcSetInerruptionMode(t_enRtcInterruptionMode enInterruptionMode)
{
	int iErrVal;
//	uint8_t u8Data;
//	
//	// to set interruption mode without modify other configuration, first we read the actual config from control register then update INTCN (bit 2) and write data back to control register
//	iErrVal=iRtc_ReadByte(DS3231_REGISTER_ADDR_CONTROL, &u8Data);
//	if(!iErrVal)
//	{
//		if(enInterruptionMode == RtcInterruptionMode_SquareWave)
//		{
//			// set bit 2 to enable square wave interruption
//			u8Data |= 0x01<<2;
//		}
//		else
//		{
//			// clear bit 2 to enable Alarm Interruption
//			u8Data &= ~(0x01<<2);
//		}
//		iErrVal=iRtc_WriteByte(DS3231_REGISTER_ADDR_CONTROL, u8Data);
//	}
	
	uint8_t control ;
	iRtc_ReadByte(DS3231_REGISTER_ADDR_CONTROL, &control);
	iRtc_WriteByte(DS3231_REGISTER_ADDR_CONTROL, (control & 0xfb) | ((1 & 0x01) << 2));
	
	return iErrVal;
}

int iRtcEnableAlarm1()
{
	int iErrVal;
	uint8_t u8Data;
	
	// to enable Alarm1 without modify other configuration, first we read the actual config from control register then set A1IE (bit 0) and write data back to control register
	iErrVal=iRtc_ReadByte(DS3231_REGISTER_ADDR_CONTROL, &u8Data);
	if(!iErrVal)
	{
		// set bit 0 to enable Alarm1
		u8Data |= 0x01;
		iErrVal=iRtc_WriteByte(DS3231_REGISTER_ADDR_CONTROL, u8Data);
	}
	
	return iErrVal;
}

int iRtcEnableAlarm2()
{
	int iErrVal;
	uint8_t u8Data;
	
	// to enable Alarm2 without modify other configuration, first we read the actual config from control register then set A2IE (bit 1) and write data back to control register
	iErrVal=iRtc_ReadByte(DS3231_REGISTER_ADDR_CONTROL, &u8Data);
	if(!iErrVal)
	{
		// set bit 1 to enable Alarm2
		u8Data |= 0x02;
		iErrVal=iRtc_WriteByte(DS3231_REGISTER_ADDR_CONTROL, u8Data);
	}
	
	return iErrVal;
}

int iRtcDisableAlarm1()
{
	int iErrVal;
	uint8_t u8Data;
	
	// to disable Alarm1 without modify other configuration, first we read the actual config from control register then clear A1IE (bit 0) and write data back to control register
	iErrVal=iRtc_ReadByte(DS3231_REGISTER_ADDR_CONTROL, &u8Data);
	if(!iErrVal)
	{
		// clear bit 0 to disable Alarm1
		u8Data &= ~0x01;
		iErrVal=iRtc_WriteByte(DS3231_REGISTER_ADDR_CONTROL, u8Data);
	}
	
	return iErrVal;
}

int iRtcDisableAlarm2()
{
	int iErrVal;
	uint8_t u8Data;
	
	// to disable Alarm2 without modify other configuration, first we read the actual config from control register then clear A2IE (bit 1) and write data back to control register
	iErrVal=iRtc_ReadByte(DS3231_REGISTER_ADDR_CONTROL, &u8Data);
	if(!iErrVal)
	{
		// clear bit 2 to disable Alarm1
		u8Data &= ~0x02;
		iErrVal=iRtc_WriteByte(DS3231_REGISTER_ADDR_CONTROL, u8Data);
	}
	
	return iErrVal;
}

int iRtcClearAlarm1InteeruptionFlag()
{
	int iErrVal;
	uint8_t u8Data;
	
	// to clear Alarm1 interruption flag, first we read Status Register, clear A1F (bit0) then write it back to Status Register
	iErrVal=iRtc_ReadByte(DS3231_REGISTER_ADDR_CONTROL_STATUS, &u8Data);
	if(!iErrVal)
	{
		// clear bit 0 to clear Alarm1 flag
		u8Data &= ~0x01;
		iErrVal=iRtc_WriteByte(DS3231_REGISTER_ADDR_CONTROL_STATUS, u8Data);
	}
	
	return iErrVal;
}

int iRtcClearAlarm2InteeruptionFlag()
{
	int iErrVal;
	uint8_t u8Data;
	
	// to clear Alarm2 interruption flag, first we read Status Register, clear A2F (bit1) then write it back to Status Register
	iErrVal=iRtc_ReadByte(DS3231_REGISTER_ADDR_CONTROL_STATUS, &u8Data);
	if(!iErrVal)
	{
		// clear bit 1 to clear Alarm2 flag
		u8Data &= ~0x02;
		iErrVal=iRtc_WriteByte(DS3231_REGISTER_ADDR_CONTROL_STATUS, u8Data);
	}
	
	return iErrVal;
}

int iRtcSetSeconds(uint8_t u8Seconds)
{
	int iErrVal;
	uint8_t u8Data;
	
	u8Data = u8Ds3231SecondsCoder(u8Seconds);
	iErrVal=iRtc_WriteByte(DS3231_REGISTER_ADDR_SECONDS, u8Data);
	if(!iErrVal)
	{
		printf("iRtcSetSeconds: succ set %u=>0x%02X\r\n", u8Seconds, u8Data);
	}
	else
	{
		printf("iRtcSetSeconds: fail set %u=>0x%02X\r\n", u8Seconds, u8Data);
	}
	
	return iErrVal;
}	

int iRtcGetSeconds(uint8_t* pu8Seconds)
{
	int iErrVal;
	uint8_t u8Data;
	
	iErrVal=iRtc_ReadByte(DS3231_REGISTER_ADDR_SECONDS, &u8Data);
	if(!iErrVal)
	{
		*pu8Seconds = u8Ds3231SecondsDecoder(u8Data);
		printf("iRtcGetSeconds: succ get 0x%02X=>%u\r\n", u8Data, *pu8Seconds);
	}
	else
	{
		printf("iRtcGetSeconds: fail\r\n");
	}
	
	return iErrVal;
}

// set datetime S:M:H DD:MM:YYYY in RTC in one go
// parameters: xDateTime(the date time to save)
// returns: if succ return 0 otherwise return error value (-1:failure)
int iRtcSetDateTime(t_xRtcDateTime xDateTime)
{
	printf("iRtcSetDateTime:\r\n");
	int iErrVal=0;
	
	// senconds, minutes, hours, days, date, monthes, years
	uint8_t pu8Data[7] = {0,0,0,0,0,0,0};
	
	pu8Data[0] = u8Ds3231SecondsCoder(xDateTime.u8Seconds);
	pu8Data[1] = u8Ds3231MinutesCoder(xDateTime.u8Minutes);
	//pu8Data[2] = u8Ds3231HoursCoder(xDateTime.u8Hours, true, 0);
	pu8Data[2] = u8Ds3231Hours24FormatCoder(xDateTime.u8Hours);
	pu8Data[3] = 0;	// day
	pu8Data[4] = u8Ds3231DateCoder(xDateTime.u8Date);
	pu8Data[5] = u8Ds3231MonthCoder(xDateTime.u8Month);
	pu8Data[6] = u8Ds3231YearCoder(xDateTime.u16Year);
	// set date and time in RTC in one read starting from address 0x00(seconds) to 0x06(years)
	iErrVal = iRtc_WriteNBytes(DS3231_REGISTER_ADDR_SECONDS, &pu8Data[0], 7);
	
	return iErrVal;
}

// get current datetime S:M:H DD:MM:YYYY from RTC in one read
// parameters: xCurrentDateTimeOut(where to store the datetime)
// returns: if succ return 0 otherwise return error value (-1:failure)
int iRtcGetCurrentDateTime(t_xRtcDateTime* xCurrentDateTimeOut)
{
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	printf("iRtcGetCurrentDateTime:\r\n");
	#endif
	int iErrVal=0;
	
	// senconds, minutes, hours, days, date, monthes, years
	uint8_t pu8Data[7] = {0,0,0,0,0,0,0};
	
	// get date and time from RTC in one read starting from address 0x00(seconds) to 0x06(years)
	iErrVal = iRtc_ReadNBytes(DS3231_REGISTER_ADDR_SECONDS, 7, &pu8Data[0]);
	if(!iErrVal)
	{
		xCurrentDateTimeOut->u8Seconds = u8Ds3231SecondsDecoder(pu8Data[0]);
		xCurrentDateTimeOut->u8Minutes = u8Ds3231MinutesDecoder(pu8Data[1]);
		//vDs3231HoursDecoder(pu8Data[2], &(xCurrentDateTimeOut->u8Hours), NULL, NULL);
		xCurrentDateTimeOut->u8Hours = u8Ds3231Hours24FormatDecoder(pu8Data[2]);
		xCurrentDateTimeOut->u8Date = u8Ds3231DateDecoder(pu8Data[4]);
		xCurrentDateTimeOut->u8Month = u8Ds3231MonthDecoder(pu8Data[5]);
		xCurrentDateTimeOut->u16Year = u16Ds3231YearDecoder(pu8Data[6]);
	}
	
	return iErrVal;
}





// set Alarm1 datetime S:M:H DD:MM:YYYY in RTC in one go
// parameters:enAlarmRate(alarm mode rate) and xDateTime(pointer to date time for alarm 1, if once per second or minute mode used, then can set this parameter to null)
// returns: if succ return 0 otherwise return error value (-1:failure)
int iRtcSetAlarm(t_enRtcAlarmRate enAlarmRate, t_xRtcDateTime* xAlarm1DateTime)
{
	#if(RTC_DEBUG > RTC_DEBUG_LVL_0)
	printf("iRtcSetDateTime:\r\n");
	#endif
	int iErrVal=0;
	
	// alarm1 hase 4 registers and alarm 2 has 3 registers
	uint8_t pu8Data[4] = {0,0,0,0};
	
	if(enAlarmRate == enRtcAlarmRate_A1_PerSecond)
	{
		// set A1M1 A1M2 A1M3 A1M4 without modify the other bits
		iErrVal = iRtc_ReadNBytes(DS3231_REGISTER_ADDR_ALARM1_SECONDS, 4, &pu8Data[0]);
		if(!iErrVal)
		{
			pu8Data[0] |= 0x80;
			pu8Data[1] |= 0x80;
			pu8Data[2] |= 0x80;
			pu8Data[3] |= 0x80;
			iErrVal = iRtc_WriteNBytes(DS3231_REGISTER_ADDR_ALARM1_SECONDS, &pu8Data[0], 4);
		}
	}
	else if(enAlarmRate == enRtcAlarmRate_A2_PerMinute)
	{
		// set A2M2 A2M3 A2M4 without modify the other bits
		iErrVal = iRtc_ReadNBytes(DS3231_REGISTER_ADDR_ALARM2_MINUTES, 3, &pu8Data[0]);
		if(!iErrVal)
		{
			pu8Data[0] |= 0x80;
			pu8Data[1] |= 0x80;
			pu8Data[2] |= 0x80;
			iErrVal = iRtc_WriteNBytes(DS3231_REGISTER_ADDR_ALARM2_MINUTES, &pu8Data[0], 3);
		}
	}
	else
	{
		// future use
	}

	return iErrVal;
}