/*
 * Gyroscope_l3gd20.c
 *
 *  Created on: Nov 17, 2022
 *      Author: shado
 */

#include "Gyroscope_l3gd20.h"
#include "main.h"

bool bWriteDataInGyro(SPI_HandleTypeDef* hspi, uint8_t u8Address, uint8_t* pu8DataIn, uint16_t u16NbrData, bool bIsDoubleCheckEnabled);


bool bWriteDataInGyro(SPI_HandleTypeDef* hspi, uint8_t u8Address, uint8_t* pu8DataIn, uint16_t u16NbrData, bool bIsDoubleCheckEnabled)
{
	bool bRetValue=false;
	uint8_t u8TmpAddress;
	uint8_t u8RxData;
	uint16_t i;

	u8TmpAddress = u8Address | GYROSCOPE_WRITE_CMD; // register address to write to
	if(u16NbrData>1)
	{
		u8TmpAddress |= GYROSCOPE_RW_MULTIPLE_ADDR_CMD;
	}
	else
	{
		u8TmpAddress |= GYROSCOPE_RW_SINGLE_ADDR_CMD;
	}

	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	osDelay(1);// wait before communicate with sensor

	if(HAL_SPI_Transmit(hspi, &u8TmpAddress, 1, 100) == HAL_OK)
	{
		if(HAL_SPI_Transmit(hspi, pu8DataIn, u16NbrData, 100) == HAL_OK)
		{
			bRetValue = true;
			if(bIsDoubleCheckEnabled)
			{
				// check if configuration is correctly done
				// we need to release the gyroscope and select it again to manage to set the address we want to Read(/Write) from(/in)
				HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
				u8TmpAddress = u8Address | GYROSCOPE_READ_CMD; // register address to read from
				if(u16NbrData>1)
				{
					u8TmpAddress |= GYROSCOPE_RW_MULTIPLE_ADDR_CMD;
				}
				else
				{
					u8TmpAddress |= GYROSCOPE_RW_SINGLE_ADDR_CMD;
				}
				HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
				osDelay(1);// wait before communicate with sensor
				if(HAL_SPI_Transmit(hspi, &u8TmpAddress, 1, 100) == HAL_OK)
				{
					for(i=0; i<u16NbrData; i++)
					{
						if(HAL_SPI_Receive(hspi, &u8RxData, 1, 100) == HAL_OK)
						{
							printf("register addr = %x, send data(%x) == received data(%x)\r\n", u8TmpAddress, pu8DataIn[i], u8RxData);
							if(u8RxData != pu8DataIn[i])
							{
								bRetValue = false;
								break; // exit loop since one data was incorrect
							}
						}
					}
				}
			}
		}
	}
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);

	return bRetValue;
}


bool bGyroIsExist(SPI_HandleTypeDef* hspi)
{
	bool bRetValue=false;
	uint8_t u8TxData = GYROSCOPE_REG_ADDR_WHO_AM_I | GYROSCOPE_READ_CMD;
	uint8_t u8RxData;

	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	osDelay(1);// wait before communiate with sensor
	if(HAL_SPI_Transmit(hspi, &u8TxData, 1, 1000) == HAL_OK)
	{
		if(HAL_SPI_Receive(hspi, &u8RxData, 1, 1000) == HAL_OK)
		{
			if(u8RxData==GYROSCOPE_REG_DEFAULT_WHO_AM_I)
			{
				bRetValue = true;
			}
		}
	}
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);

	return bRetValue;
}

//bool bGyroConfiguration(SPI_HandleTypeDef* hspi)
//{
//	bool bRetValue=false;
//	uint8_t u8TxData[2];
//	uint8_t u8RxData;
//
//	u8TxData[0] = GYROSCOPE_REG_ADDR_FIFO_CTRL_REG | GYROSCOPE_WRITE_CMD; // register address to write to
//	u8TxData[1] = GYROSCOPE_FIFO_MODE_CONFI_BYPASS; // data
//	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
//	osDelay(1);// wait before communiate with sensor
//	if(HAL_SPI_Transmit(hspi, (uint8_t*)u8TxData, 2, 100) == HAL_OK)
//	{
//		// check if configuration is correctly done
//		// we need to diselect the gyroscope and select it again to manage to set the address we want to Read(/Write) from(/in)
//		HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
//		u8TxData[0] = GYROSCOPE_REG_ADDR_FIFO_CTRL_REG | GYROSCOPE_READ_CMD;
//		HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
//		osDelay(1);// wait before communiate with sensor
//		if(HAL_SPI_Transmit(hspi, &(u8TxData[0]), 1, 100) == HAL_OK)
//		{
//			if(HAL_SPI_Receive(hspi, &u8RxData, 1, 100) == HAL_OK)
//			{
//				//printf("register addr = %x, send data(%x) == received data(%x)\r\n", u8TxData[0], u8TxData[1], u8RxData);
//				if(u8RxData==GYROSCOPE_FIFO_MODE_CONFI_BYPASS)
//				{
//					bRetValue = true;
//				}
//			}
//		}
//	}
//	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
//
//	return bRetValue;
//}

bool bGyroConfiguration(SPI_HandleTypeDef* hspi)
{
	bool bRetValue;
	uint8_t u8Configuration;

	// CTRL REG1 register config
	u8Configuration = GYROSCOPE_CTRL_REG1_PD_DISABLE | GYROSCOPE_CTRL_REG1_X_ENABLE | GYROSCOPE_CTRL_REG1_Y_ENABLE | GYROSCOPE_CTRL_REG1_Z_ENABLE;
	bRetValue = bWriteDataInGyro(hspi, GYROSCOPE_REG_ADDR_CTRL_REG1, &u8Configuration, 1, true);

	// CTRL REG4 register config
	u8Configuration = GYROSCOPE_CTRL_REG4_BDU_ENABLE | GYROSCOPE_CTRL_REG4_BLE_LITTLE_ENDIAN | GYROSCOPE_CTRL_REG4_FS_250_DPS | GYROSCOPE_CTRL_REG4_SIM_4_WIRE;
	bRetValue = bWriteDataInGyro(hspi, GYROSCOPE_REG_ADDR_CTRL_REG4, &u8Configuration, 1, true);

	// FIFO register config
	u8Configuration = GYROSCOPE_FIFO_MODE_CONFI_BYPASS;
	bRetValue = bWriteDataInGyro(hspi, GYROSCOPE_REG_ADDR_FIFO_CTRL_REG, &u8Configuration, 1, true);
}

bool bGayroGetXYZ(SPI_HandleTypeDef* hspi, float* x, float* y, float* z)
{
	bool bRetValue = true;
	uint8_t u8TxData;
	uint8_t u8RxData[2];
	int16_t i16TmpX;
	int16_t i16TmpY;
	int16_t i16TmpZ;

	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET); // this line, just in case the CS was low

	// read X
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	osDelay(1);// wait before communicate with sensor
	u8TxData = GYROSCOPE_REG_ADDR_OUT_X_L | GYROSCOPE_READ_CMD | GYROSCOPE_RW_MULTIPLE_ADDR_CMD;
	if(HAL_SPI_Transmit(hspi, &u8TxData, 1, 100) == HAL_OK)
	{
		if(HAL_SPI_Receive(hspi, u8RxData, 2, 100) == HAL_OK)
		{
			i16TmpX = u8RxData[1]<<8 | u8RxData[0];
		}
		else
		{
			bRetValue = false;
		}
	}
	else
	{
		bRetValue = false;
	}
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
	*x = i16TmpX * GYROSCOPE_SENSITIVITY_FS_250;

	// read Y
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	osDelay(1);// wait before communicate with sensor
	u8TxData = GYROSCOPE_REG_ADDR_OUT_Y_L | GYROSCOPE_READ_CMD | GYROSCOPE_RW_MULTIPLE_ADDR_CMD;
	if(HAL_SPI_Transmit(hspi, &u8TxData, 1, 100) == HAL_OK)
	{
		if(HAL_SPI_Receive(hspi, u8RxData, 2, 100) == HAL_OK)
		{
			i16TmpY = u8RxData[1]<<8 | u8RxData[0];
		}
		else
		{
			bRetValue = false;
		}
	}
	else
	{
		bRetValue = false;
	}
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
	*y = i16TmpY * GYROSCOPE_SENSITIVITY_FS_250;

	// read Z
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	osDelay(1);// wait before communicate with sensor
	u8TxData = GYROSCOPE_REG_ADDR_OUT_Z_L | GYROSCOPE_READ_CMD | GYROSCOPE_RW_MULTIPLE_ADDR_CMD;
	if(HAL_SPI_Transmit(hspi, &u8TxData, 1, 100) == HAL_OK)
	{
		if(HAL_SPI_Receive(hspi, u8RxData, 2, 100) == HAL_OK)
		{
			i16TmpZ = u8RxData[1]<<8 | u8RxData[0];
		}
		else
		{
			bRetValue = false;
		}
	}
	else
	{
		bRetValue = false;
	}

	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
	*z = i16TmpZ * GYROSCOPE_SENSITIVITY_FS_250;

	return bRetValue;
}
