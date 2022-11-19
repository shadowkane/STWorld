/*
 * Gyroscope_l3gd20.h
 *
 *  Created on: Nov 17, 2022
 *      Author: shado
 */

#ifndef SENSORS_GYROSCOPE_GYROSCOPE_L3GD20_H_
#define SENSORS_GYROSCOPE_GYROSCOPE_L3GD20_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

/* COMMANDS*/
#define GYROSCOPE_READ_CMD					0x80
#define GYROSCOPE_WRITE_CMD					0x00
#define GYROSCOPE_RW_MULTIPLE_ADDR_CMD		0x40 // for multiple reading or writing
#define GYROSCOPE_RW_SINGLE_ADDR_CMD		0x00 // for single reading or writing

/* CTRL_REG1 field configuration */
// PD: Power Down
#define GYROSCOPE_CTRL_REG1_PD_START_POS		3
#define GYROSCOPE_CTRL_REG1_PD_MASK				0x08
#define GYROSCOPE_CTRL_REG1_PD_ENABLE			0x00 // activate power down mode
#define GYROSCOPE_CTRL_REG1_PD_DISABLE			0x08 // activate normal or sleep mode
// Zen: Z axis enable
#define GYROSCOPE_CTRL_REG1_Z_START_POS			2
#define GYROSCOPE_CTRL_REG1_Z_MASK				0x04
#define GYROSCOPE_CTRL_REG1_Z_ENABLE			0x04
#define GYROSCOPE_CTRL_REG1_Z_DISABLE			0x00
// Yen: Y axis enable
#define GYROSCOPE_CTRL_REG1_Y_START_POS			1
#define GYROSCOPE_CTRL_REG1_Y_MASK				0x02
#define GYROSCOPE_CTRL_REG1_Y_ENABLE			0x02
#define GYROSCOPE_CTRL_REG1_Y_DISABLE			0x00
// Xen: X axis enable
#define GYROSCOPE_CTRL_REG1_X_START_POS			0
#define GYROSCOPE_CTRL_REG1_X_MASK				0x01
#define GYROSCOPE_CTRL_REG1_X_ENABLE			0x01
#define GYROSCOPE_CTRL_REG1_X_DISABLE			0x00

/* CTRL_REG4 field configuration */
// BDU: Block Data Update
#define GYROSCOPE_CTRL_REG4_BDU_START_POS		7
#define GYROSCOPE_CTRL_REG4_BDU_MASK			0x80
#define GYROSCOPE_CTRL_REG4_BDU_ENABLE			0x80
#define GYROSCOPE_CTRL_REG4_BDU_DISABLE			0x00
// BLE: Big Little Endian
#define GYROSCOPE_CTRL_REG4_BLE_START_POS		6
#define GYROSCOPE_CTRL_REG4_BLE_MASK			0x40
#define GYROSCOPE_CTRL_REG4_BLE_LITTLE_ENDIAN	0x00
#define GYROSCOPE_CTRL_REG4_BLE_BIG_ENDIAN		0x40
// FS: Full scale
#define GYROSCOPE_CTRL_REG4_FS_START_POS		4
#define GYROSCOPE_CTRL_REG4_FS_MASK				0x30
#define GYROSCOPE_CTRL_REG4_FS_250_DPS			0x00
#define GYROSCOPE_CTRL_REG4_FS_500_DSP			0x10
#define GYROSCOPE_CTRL_REG4_FS_2000_DSP			0x20 //0x30 also for 200DPS
// SIM: SPI serial interface mode selection
#define GYROSCOPE_CTRL_REG4_SIM_START_POS		0
#define GYROSCOPE_CTRL_REG4_SIM_MASK			0x01
#define GYROSCOPE_CTRL_REG4_SIM_4_WIRE			0x00
#define GYROSCOPE_CTRL_REG4_SIM_3_WIRE			0x01

/* FIFO mode configuration */
// start position
#define GYROSCOPE_FIFO_MODE_CONFI_START_POS				0
// mask
#define GYROSCOPE_FIFO_MODE_CONFI_MASK				0x07
// modes
#define GYROSCOPE_FIFO_MODE_CONFI_BYPASS			0x00
#define GYROSCOPE_FIFO_MODE_CONFI_FIFO				0x01
#define GYROSCOPE_FIFO_MODE_CONFI_STREAM			0x02
#define GYROSCOPE_FIFO_MODE_CONFI_STREAM_TO_FIFO	0x03
#define GYROSCOPE_FIFO_MODE_CONFI_BYPASS_TO_STREAM	0x04

/*REGISTER MAP*/
#define GYROSCOPE_REG_ADDR_WHO_AM_I			0x0F	//Read only
#define GYROSCOPE_REG_ADDR_CTRL_REG1		0x20	//Read and Write
#define GYROSCOPE_REG_ADDR_CTRL_REG2		0x21	//Read and Write
#define GYROSCOPE_REG_ADDR_CTRL_REG3		0x22	//Read and Write
#define GYROSCOPE_REG_ADDR_CTRL_REG4		0x23	//Read and Write
#define GYROSCOPE_REG_ADDR_CTRL_REG5		0x24	//Read and Write
#define GYROSCOPE_REG_ADDR_REFERENCE		0x25	//Read and Write
#define GYROSCOPE_REG_ADDR_OUT_TEMP			0x26	//Read only
#define GYROSCOPE_REG_ADDR_STATUS_REG		0x27	//Read only
#define GYROSCOPE_REG_ADDR_OUT_X_L			0x28	//Read only
#define GYROSCOPE_REG_ADDR_OUT_X_H			0x29	//Read only
#define GYROSCOPE_REG_ADDR_OUT_Y_L			0x2A	//Read only
#define GYROSCOPE_REG_ADDR_OUT_Y_H			0x2B	//Read only
#define GYROSCOPE_REG_ADDR_OUT_Z_L			0x2C	//Read only
#define GYROSCOPE_REG_ADDR_OUT_Z_H			0x2D	//Read only
#define GYROSCOPE_REG_ADDR_FIFO_CTRL_REG	0x2E	//Read and Write
#define GYROSCOPE_REG_ADDR_FIFO_SRC_REG		0x2F	//Read only
#define GYROSCOPE_REG_ADDR_INT1_CFG			0x30	//Read and Write
#define GYROSCOPE_REG_ADDR_INT1_SRC			0x31	//Read only
#define GYROSCOPE_REG_ADDR_INT1_TSH_XH		0x32	//Read and Write
#define GYROSCOPE_REG_ADDR_INT1_TSH_XL		0x33	//Read and Write
#define GYROSCOPE_REG_ADDR_INT1_TSH_YH		0x34	//Read and Write
#define GYROSCOPE_REG_ADDR_INT1_TSH_YL		0x35	//Read and Write
#define GYROSCOPE_REG_ADDR_INT1_TSH_ZH		0x36	//Read and Write
#define GYROSCOPE_REG_ADDR_INT1_TSH_ZL		0x37	//Read and Write
#define GYROSCOPE_REG_ADDR_INT1_DURATION	0x38	//Read and Write

/*Register Default Value */
#define GYROSCOPE_REG_DEFAULT_WHO_AM_I		0xD4

/* Default values */
//#define GYROSCOPE_SENSITIVITY_MDPS_DIGIT_FS_250		(8.75F)
//#define GYROSCOPE_SENSITIVITY_MDPS_DIGIT_FS_500		(17.5F)
//#define GYROSCOPE_SENSITIVITY_MDPS_DIGIT_FS_2000	(70F)
#define GYROSCOPE_SENSITIVITY_FS_250	(0.00875F)
#define GYROSCOPE_SENSITIVITY_FS_500	(0.0175F)
#define GYROSCOPE_SENSITIVITY_FS_2000	(0.07F)

/*Function*/
bool bGyroIsExist(SPI_HandleTypeDef* hspi);
bool bGyroConfiguration(SPI_HandleTypeDef* hspi);
bool bGayroGetXYZ(SPI_HandleTypeDef* hspi, float* x, float* y, float* z);

#endif /* SENSORS_GYROSCOPE_GYROSCOPE_L3GD20_H_ */
