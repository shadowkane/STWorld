/*
 * sht35.h
 *
 *  Created on: May 12, 2023
 *      Author: shado
 */

#ifndef DRIVERS_BSP_COMPONENTS_SHT35_H_
#define DRIVERS_BSP_COMPONENTS_SHT35_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "global.h"

//#define 	SHT35_DEFAULT_I2C_ADDR_PIN_LOW 					0x44
//#define 	SHT35_DEFAULT_I2C_ADDR_PIN_HIGH					0x45
#define     SHT35_DEFAULT_I2C_ADDR							0x8a//0x45(default address) and shift left by 1 bit because it's 7 bit address => 0x45<<1 = 0x8a
#define		SHT35_DEFAULT_I2C_TIMEOUT						0x3000
#define 	SHT35_MAX_MEASUREMENT_DURATION_FOR_REPEAT_HIGH	15//ms
#define 	SHT35_MAX_MEASUREMENT_DURATION_FOR_REPEAT_MED	6//ms
#define 	SHT35_MAX_MEASUREMENT_DURATION_FOR_REPEAT_LOW	4//ms
//**** Single Shot Data Acquisition mode commands ****//
//#define		SHT35_SSDAQ_MODE_CLK_STRETCH_POS		8
//#define		SHT35_SSDAQ_MODE_CLK_STRETCH_MASK		0xff00
//
//#define		SHT35_SSDAQ_MODE_REPEAT_POS		0
//#define		SHT35_SSDAQ_MODE_REPEAT_MASK		0x00ff

#define		SHT35_CMD_SSDAQ_MODE_CLK_STRETCH_ENABLED_REPEAT_HIGH	0x2c06
#define		SHT35_CMD_SSDAQ_MODE_CLK_STRETCH_ENABLED_REPEAT_MED		0x2c0d
#define		SHT35_CMD_SSDAQ_MODE_CLK_STRETCH_ENABLED_REPEAT_LOW		0x2c10
#define		SHT35_CMD_SSDAQ_MODE_CLK_STRETCH_DISABLED_REPEAT_HIGH	0x2400
#define		SHT35_CMD_SSDAQ_MODE_CLK_STRETCH_DISABLED_REPEAT_MED	0x240b
#define		SHT35_CMD_SSDAQ_MODE_CLK_STRETCH_DISABLED_REPEAT_LOW	0x2416

//**** Periodic Data Acquisition mode commands ****//
//#define		SHT35_PDAQ_MODE_MPS_POS		8
//#define		SHT35_PDAQ_MODE_MPS_MASK		0xff00
//
//#define		SHT35_PDAQ_MODE_REPEAT_POS		0
//#define		SHT35_PDAQ_MODE_REPEAT_MASK		0x00ff

#define		SHT35_CMD_PDAQ_MODE_MPS_05_REPEAT_HIGH	0x2032
#define		SHT35_CMD_PDAQ_MODE_MPS_05_REPEAT_MED	0x2024
#define		SHT35_CMD_PDAQ_MODE_MPS_05_REPEAT_LOW	0x202f
#define		SHT35_CMD_PDAQ_MODE_MPS_1_REPEAT_HIGH	0x2130
#define		SHT35_CMD_PDAQ_MODE_MPS_1_REPEAT_MED	0x2126
#define		SHT35_CMD_PDAQ_MODE_MPS_1_REPEAT_LOW	0x212d
#define		SHT35_CMD_PDAQ_MODE_MPS_2_REPEAT_HIGH	0x2236
#define		SHT35_CMD_PDAQ_MODE_MPS_2_REPEAT_MED	0x2220
#define		SHT35_CMD_PDAQ_MODE_MPS_2_REPEAT_LOW	0x222b
#define		SHT35_CMD_PDAQ_MODE_MPS_4_REPEAT_HIGH	0x2334
#define		SHT35_CMD_PDAQ_MODE_MPS_4_REPEAT_MED	0x2322
#define		SHT35_CMD_PDAQ_MODE_MPS_4_REPEAT_LOW	0x2329
#define		SHT35_CMD_PDAQ_MODE_MPS_10_REPEAT_HIGH	0x2737
#define		SHT35_CMD_PDAQ_MODE_MPS_10_REPEAT_MED	0x2721
#define		SHT35_CMD_PDAQ_MODE_MPS_10_REPEAT_LOW	0x272a

#define 	SHT35_CMD_PDAQ_MODE_FETCH_DATA			0xe000	//fetch data cmd will initiate the transmission of measurement in Periodic mode to read them
#define		SHT35_CMD_PDAQ_MODE_BREAK				0x3093	// stop Periodic mode (recommended to stop periodic mode before sending any cmd except for the fetch cmd)

//**** HEAT commands ****//
#define		SHT35_CMD_ENABLE_HEAT			0x306D
#define		SHT35_CMD_DISABLE_HEAT			0x3066

//**** Reset commands ****//
#define		SHT35_CMD_SOFT_RST				0x30A2	// reset device without removing power

//**** Status register commands ****//
#define		SHT35_CMD_READ_STATUS_REG		0xF32D
#define		SHT35_CMD_CLEAR_STATUS_REG		0x3041


void vSht35Config(I2C_HandleTypeDef* pxI2cHandler);
bool bSht35Init();
bool bSht35GetTemperature(float* pfTemperatureValue, enTemperatureUnit_t enUnit);
bool bSht35GetHumidity(float* pfHumidityValue);
bool bSht35GetTemperatureAndHumidity(float* pfTemperatureValue, enTemperatureUnit_t enUnit, float* pfHumidityValue);

#define     CMD_READ_HIGH_ALERT_LIMIT_SET_VALUE     0XE11F
#define     CMD_READ_HIGH_ALERT_LIMIT_CLEAR_VALUE   0XE114
#define     CMD_READ_LOW_ALERT_LIMIT_SET_VALUE      0XE102
#define     CMD_READ_LOW_ALERT_LIMIT_CLEAR_VALUE    0XE109

#define     CMD_WRITE_HIGH_ALERT_LIMIT_SET_VALUE    0X611D
#define     CMD_WRITE_HIGH_ALERT_LIMIT_CLEAR_VALUE  0X6116
#define     CMD_WRITE_LOW_ALERT_LIMIT_SET_VALUE     0X6100
#define     CMD_WRITE_LOW_ALERT_LIMIT_CLEAR_VALUE     0X610B




#endif /* DRIVERS_BSP_COMPONENTS_SHT35_H_ */
