/*
 * global.h
 *
 *  Created on: May 14, 2023
 *      Author: shado
 */

#ifndef APPLICATION_USER_GLOBAL_H_
#define APPLICATION_USER_GLOBAL_H_


// Temperature unit available and type that will be used for the whole project
typedef enum _enTemperatureUnit_t
{
	enTemperatureUnitC = 0,
	entemperatureUnitF
}enTemperatureUnit_t;

#define printf_float(fValue)	printf("%d.%d", (int)fValue, ((int)(fValue*1000)-(((int)fValue)*1000)) )

#endif /* APPLICATION_USER_GLOBAL_H_ */
