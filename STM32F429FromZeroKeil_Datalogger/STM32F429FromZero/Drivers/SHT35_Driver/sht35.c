/*
 * sht35.c
 *
 *  Created on: May 12, 2023
 *      Author: shado
 */

#include "sht35.h"
#include <stdio.h>
#include <stdint.h>

static I2C_HandleTypeDef *hi2c;
//static bool bReadByteFromAddress(uint16_t u16RegAddr, uint8_t* pu8RegData);
static bool bReadWordFromAddress(uint16_t u16RegAddr, uint16_t* pu16RegData);
static bool bReadnBytesFromAddress(uint16_t u16RegAddr, uint8_t* pu8Data, uint16_t u16DataLength);
static bool bReadnBytes(uint8_t* pu8Data, uint16_t u16DataLength);
//static bool bWriteByteInAddres(uint16_t u16RegAddr, uint8_t* pu8RegData);
static bool bWriteWordInAddre(uint16_t u16RegAddr, uint16_t* pu16RegData);
static bool bSendCmd(uint16_t u16Cmd);
static float fTemperatureConversion(int iTemperatureRawValue, enTemperatureUnit_t enUnit);

//static bool bReadByteFromAddress(uint16_t u16RegAddr, uint8_t* pu8RegData)
//{
//	bool bRetValue = false;
//
//	if(HAL_I2C_Mem_Read(hi2c, SHT35_DEFAULT_I2C_ADDR, u16RegAddr, I2C_MEMADD_SIZE_16BIT, pu8RegData, 1, SHT35_DEFAULT_I2C_TIMEOUT) == HAL_OK)
//	{
//		bRetValue = true;
//	}
//
//	return bRetValue;
//}

static bool bReadWordFromAddress(uint16_t u16RegAddr, uint16_t* pu16RegData)
{
	bool bRetValue = false;
	HAL_StatusTypeDef enStatus;

	enStatus = HAL_I2C_Mem_Read(hi2c, SHT35_DEFAULT_I2C_ADDR, u16RegAddr, I2C_MEMADD_SIZE_16BIT, (uint8_t*)pu16RegData, 2, SHT35_DEFAULT_I2C_TIMEOUT);
	if(enStatus == HAL_OK)
	{
		*pu16RegData = ((*pu16RegData&0xff00U) >> 8) | ((*pu16RegData&0x00ffU) << 8);
		bRetValue = true;
	}

	return bRetValue;
}

static bool bReadnBytesFromAddress(uint16_t u16RegAddr, uint8_t* pu8Data, uint16_t u16DataLength)
{
	bool bRetValue = false;

	if(HAL_I2C_Mem_Read(hi2c, SHT35_DEFAULT_I2C_ADDR, u16RegAddr, I2C_MEMADD_SIZE_16BIT, pu8Data,u16DataLength, SHT35_DEFAULT_I2C_TIMEOUT) == HAL_OK)
	{
		bRetValue = true;
	}

	return bRetValue;
}

static bool bReadnBytes(uint8_t* pu8Data, uint16_t u16DataLength)
{
	bool bRetValue = false;

	if(HAL_I2C_Master_Receive(hi2c, SHT35_DEFAULT_I2C_ADDR, pu8Data, u16DataLength, SHT35_DEFAULT_I2C_TIMEOUT) == HAL_OK)
	{
		bRetValue = true;
	}

	return bRetValue;
}

//static bool bWriteByteInAddre(uint16_t u16RegAddr, uint8_t* pu8RegData)
//{
//	bool bRetValue = false;
//
//	if(HAL_I2C_Mem_Write(hi2c, SHT35_DEFAULT_I2C_ADDR, u16RegAddr, I2C_MEMADD_SIZE_16BIT, pu8RegData, 1, SHT35_DEFAULT_I2C_TIMEOUT) == HAL_OK)
//	{
//		bRetValue = true;
//	}
//
//	return bRetValue;
//}

static bool bWriteWordInAddre(uint16_t u16RegAddr, uint16_t* pu16RegData)
{
	bool bRetValue = false;
	uint8_t pu8DataToSend[2] = {((*pu16RegData)&0xff00)>>8, (*pu16RegData)&0x00ff};

	if(HAL_I2C_Mem_Read(hi2c, SHT35_DEFAULT_I2C_ADDR, u16RegAddr, I2C_MEMADD_SIZE_16BIT, &(pu8DataToSend[0]), 2, SHT35_DEFAULT_I2C_TIMEOUT) == HAL_OK)
	{
		bRetValue = true;
	}

	return bRetValue;
}

static bool bSendCmd(uint16_t u16Cmd)
{
	bool bRetValue = false;
	uint8_t pu8Cmd[2] = {(u16Cmd&0xff00)>>8, u16Cmd&0x00ff};

	if(HAL_I2C_Master_Transmit(hi2c, SHT35_DEFAULT_I2C_ADDR, pu8Cmd, 2, SHT35_DEFAULT_I2C_TIMEOUT) == HAL_OK)
	{
		bRetValue = true;
	}

	return bRetValue;
}

static float fTemperatureConversion(int iTemperatureRawValue, enTemperatureUnit_t enUnit)
{
	float fTemperature;
	switch(enUnit)
	{
		case enTemperatureUnitC:
			// T(°C) = -45 + 175 * (RawT/(2^16-1)) => 175*(RawT/65,536-1) -45 => (RawT * 175/65,535) -45 => RawT * 0.002670 - 45
			fTemperature = (iTemperatureRawValue * 0.002670) - 45.0;
			break;
		case entemperatureUnitF:
			// T(°F) = -49 + 315 * (RawT/(2^16-1)) => 315*(RawT/65,536-1) -49 => (RawT * 315/65,535) -49 => RawT * 0.004806 - 49
			fTemperature = (iTemperatureRawValue * 0.004806) - 49.0;
			break;
		default:
			break;
	}

	return fTemperature;
}

void vSht35Config(I2C_HandleTypeDef* pxI2cHandler)
{
	uint16_t u16StatusReg;
	bool bIsOk;
	#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
	printf("SHT35 Initialization\n");
	#endif
	// set the I2C handler the driver will use
	hi2c = pxI2cHandler;
	// read status register to check if sensor exist
	bIsOk = bReadWordFromAddress(SHT35_CMD_READ_STATUS_REG, &u16StatusReg);
	#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
	if(bIsOk)
	{
		printf("Status register of SHT35 = %04X\n", u16StatusReg);
	}
	else
	{
		printf("Couldn't read Status register of SHT35\n");
	}
	#endif
	bIsOk = bSendCmd(SHT35_CMD_SOFT_RST);
	#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
	if(bIsOk)
	{
		printf("Send soft reset cmd successfully\n");
	}
	else
	{
		printf("Couldn't send soft reset CMD\n");
	}
	#endif

//	if(bSendCmd(SHT35_CMD_ENABLE_HEAT))
//	{
//		printf("Send enable heat cmd successfully\n");
//	}
//	else
//	{
//		printf("Couldn't send enable heat CMD\n");
//	}

	bIsOk = bReadWordFromAddress(SHT35_CMD_READ_STATUS_REG, &u16StatusReg);
	#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
	if(bIsOk)
	{
		printf("Status register of SHT35 = %04X\n", u16StatusReg);
	}
	else
	{
		printf("Couldn't read Status register of SHT35\n");
	}
	#endif
	
//	if(bSendCmd(SHT35_CMD_DISABLE_HEAT))
//	{
//		printf("Send enable heat cmd successfully\n");
//	}
//	else
//	{
//		printf("Couldn't send enable heat CMD\n");
//	}
	
	bIsOk = bReadWordFromAddress(SHT35_CMD_READ_STATUS_REG, &u16StatusReg);
	#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
	if(bIsOk)
	{
		printf("Status register of SHT35 = %04X\n", u16StatusReg);
	}
	else
	{
		printf("Couldn't read Status register of SHT35\n");
	}
	#endif
}

bool bSht35Init()
{
	bool bRetValue = false;
	
	if(bSendCmd(SHT35_CMD_SSDAQ_MODE_CLK_STRETCH_DISABLED_REPEAT_LOW))
	{
		#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
		printf("Send SSDAQ cmd successfully\n");
		#endif
		bRetValue = true;
	}
		#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
	else
	{
		printf("Couldn't send SSDAQ CMD\n");
	}
	#endif
	
	if(bRetValue == true)
	{
		if(!bSendCmd(SHT35_CMD_DISABLE_HEAT))
		{
			#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
			printf("Couldn't send enable heat CMD\n");
			#endif
			bRetValue = false;
		}
		#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
		else
		{
			printf("Send enable heat cmd successfully\n");
		}
		#endif
	}

	return bRetValue;
}

bool bSht35GetTemperature(float* pfTemperatureValue, enTemperatureUnit_t enUnit)
{
	bool bRetValue = false;
	uint8_t pu8Data[6] = {0,0,0,0,0,0};// 2 bytes for Temperatyre + 1 byte for CNC + 2 bytes for Humidity + 1 byte for CNC
	int iTemperatureRawValue=0;
	#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
	printf("bSht35GetTemperature");
	#endif
	if(enUnit == enTemperatureUnitC || enUnit == entemperatureUnitF)
	{
		if(bSendCmd(SHT35_CMD_SSDAQ_MODE_CLK_STRETCH_DISABLED_REPEAT_MED))
		{
			HAL_Delay(SHT35_MAX_MEASUREMENT_DURATION_FOR_REPEAT_MED); // we can use osDelay since we call this function from task (if in the future we will call it from ISR, we must change the waiting process)
			if(bReadnBytes(&(pu8Data[0]), 6))
			{
				#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
				printf("bSht35GetTemperature: data => {%x, %x, %x, %x, %x, %x}\n", pu8Data[0], pu8Data[1], pu8Data[2], pu8Data[3], pu8Data[4], pu8Data[5]);
				#endif
				iTemperatureRawValue = ( ((int16_t)pu8Data[0])<<8 ) | ((int16_t)pu8Data[1]);
				#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
				printf("bSht35GetTemperature: temperature raw value=%d\n", iTemperatureRawValue);
				#endif
				*pfTemperatureValue = fTemperatureConversion(iTemperatureRawValue, enUnit);
				#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
				printf("bSht35GetTemperature: temperature final value=%.3f\r\n", *pfTemperatureValue);
				#endif
				bRetValue = true;
			}
			#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
			else
			{
				printf("bSht35GetTemperature: Couldn't read from sensor\n");
			}
			#endif
		}
		#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
		else
		{
			printf("bSht35GetTemperature: Couldn't send cmd to sensor\n");
		}
		#endif
	}
	#if(SHT35_DEBUG > SHT_DEBUG_LVL_0)
	else
	{
		printf("bSht35GetTemperature: Wrong temperature unit\n");
	}
	#endif
	return bRetValue;
}

bool bGetHumidity(float* fHumidityValue)
{
	bool bRetValue;

	return bRetValue;
}

bool bGetTemperatureAndHumidity(float* fTemperatureValue, enTemperatureUnit_t enUnit, float* fHumidityValue)
{
	bool bRetValue;

	return bRetValue;
}
