#include "RtcDriver.h"
#include <stdio.h>
typedef struct _RtcDevice
{
	I2C_HandleTypeDef* xRtcI2cHandler;
	uint8_t u8Address;
}t_RtcDevice;

static t_RtcDevice xRtcDevice;

static int iRtc_ReadByte(uint8_t u8Register, uint8_t* pu8DataOut);
static int iRtc_ReadnBytes(uint8_t u8Register, int iBufferSize, uint8_t* pu8BufferOut);
static int iRtc_WriteByte(uint8_t u8Register, uint8_t u8DataIn);
static uint8_t u8Ds3231SecondsDecoder(uint8_t u8RawData);
static uint8_t u8Ds3231SecondsCoder(uint8_t u8Seconds);


// read 1 byte from register
// parameters: u8Register(register to read from), pu8DataOut(pointer to store data)
// returns: read results if succ return 0 otherwise return error value (-1:failure)
static int iRtc_ReadByte(uint8_t u8Register, uint8_t* pu8DataOut)
{
	int iErrVal = 0;

	// alternative method to read from I2C device
//	iErrVal = HAL_I2C_Master_Transmit(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, &u8Register, 1, HAL_MAX_DELAY);
//	if(iErrVal != HAL_OK)
//	{
//		printf("iRtc_ReadByte HAL_I2C_Master_Transmit succ\r\n");
//		iErrVal = HAL_I2C_Master_Receive(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, pu8DataOut, 1, HAL_MAX_DELAY);
//	}
	
	iErrVal = HAL_I2C_Mem_Read(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, u8Register, I2C_MEMADD_SIZE_8BIT, pu8DataOut, 1, 1000);
	if(iErrVal != HAL_OK)
	{
		printf("iRtc_ReadByte failed(0x%02X), err:%d\r\n", u8Register, iErrVal);
		iErrVal = -1;
	}
	else
	{
		printf("iRtc_ReadByte succ read (0x%02X=>0x%02X)\r\n", u8Register, *pu8DataOut);
	}
	
	return iErrVal;
}

// read n bytes from register
// parameters: u8Register(register to read from), iBufferSize(how many bytes to read also it's buffer size,) pu8DataOut(buffer to store data)
// returns: read results if succ return 0 otherwise return error value (-1:failure)
static int iRtc_ReadnBytes(uint8_t u8Register, int iBufferSize, uint8_t* pu8BufferOut)
{
	int iErrVal = 0;
	
	iErrVal = HAL_I2C_Mem_Read(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, u8Register, I2C_MEMADD_SIZE_8BIT, pu8BufferOut, iBufferSize, 1000);
	if(iErrVal != HAL_OK)
	{
		printf("iRtc_ReadByte failed(0x%02X), err:%d\r\n", u8Register, iErrVal);
		iErrVal = -1;
	}
	else
	{
		printf("iRtc_ReadByte succ read (0x%02X=>)\r\n", u8Register);
		for(int i=0; i<iBufferSize; i++)
		{		
			printf(" 0x%02X", pu8BufferOut[i]);
		}
		printf(")\r\n");
	}
		
	return iErrVal;
}

// write 1 byte in register
// parameters: u8Register(register to write in), u8DataIn(data to wrtie)
// returns: write results if succ return 0 otherwise return error value (-1:failure)
static int iRtc_WriteByte(uint8_t u8Register, uint8_t u8DataIn)
{
	int iErrVal = 0;

// alternative method to write in I2C device
//	uint8_t bytes[2] = { u8Register, u8DataIn };
//	iErrVal = HAL_I2C_Master_Transmit(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, bytes, 2, HAL_MAX_DELAY);
	
	iErrVal = HAL_I2C_Mem_Write(xRtcDevice.xRtcI2cHandler, xRtcDevice.u8Address, u8Register, I2C_MEMADD_SIZE_8BIT, &u8DataIn, 1, 1000);
	if(iErrVal != HAL_OK)
	{
		printf("iRtc_WriteByte failed(0x%02X), err:%d\r\n", u8Register, iErrVal);
		iErrVal = -1;
	}
	else
	{
		printf("iRtc_ReadByte succ write(0x%02X=>0x%02X)\r\n", u8Register, u8DataIn);
	}
	
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


void vRtcDriverConfig(I2C_HandleTypeDef* xRtcI2cHandler, uint8_t u8DeviceI2cAddress)
{
	xRtcDevice.xRtcI2cHandler = xRtcI2cHandler;
	xRtcDevice.u8Address = u8DeviceI2cAddress;
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