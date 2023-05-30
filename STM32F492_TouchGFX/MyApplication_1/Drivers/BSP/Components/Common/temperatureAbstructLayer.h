/*
 * temperatureAbstructLayer.h
 *
 *  Created on: May 14, 2023
 *      Author: shado
 */

#ifndef DRIVERS_BSP_COMPONENTS_TEMPERATUREABSTRUCTLAYER_H_
#define DRIVERS_BSP_COMPONENTS_TEMPERATUREABSTRUCTLAYER_H_

#include "global.h"

#define TEMPERATURE_SENSOR_SHT35


#ifdef TEMPERATURE_SENSOR_SHT35
	#include "Components/sht35/sht35.h"
	#define vTemperatureSensorConfig(pxI2cHandler) 							vSht35Config(pxI2cHandler)
	#define bTemperatureSensorInit()										bSht35Init()
	#define bTemperatureSensorGetTemperature(pfTemperatureValue, enUnit) 	bSht35GetTemperature(pfTemperatureValue, enUnit)
#else
	#error "Undefined temperature sensor!!"
#endif

#endif /* DRIVERS_BSP_COMPONENTS_TEMPERATUREABSRUCTLAYER_H_ */
