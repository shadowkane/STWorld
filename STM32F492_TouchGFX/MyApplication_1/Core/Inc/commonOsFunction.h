/*
 * commonOsFunction.h
 *
 *  Created on: May 5, 2023
 *      Author: shado
 */

#ifndef APPLICATION_USER_COMMONOSFUNCTION_H_
#define APPLICATION_USER_COMMONOSFUNCTION_H_

#include "cmsis_os.h"
#include <stdbool.h>
#include <stdint.h>

#define QUEUE_MSG_MAX_LENGTH_FLOAT		10
#define QUEUE_MSG_MAX_LENGTH_UINT16		20
#define QUEUE_MSG_MAX_LENGTH_UINT8		40

typedef enum _enModuleId_t
{
	enModule_BackendSystem = 0,
	enModule_Daq,
	enModule_Frontend
}enModuleId_t;

typedef enum _enQueueMsgId_t
{
	// To Backend System
	enQueueMsg_BackendSystemWaitForCmd = 0,
	enQueueMsg_BackendSystemInitDone,
	enQueueMsg_BackendSystemSetLedState,
	enQueueMsg_BackendSystemGettLedState,
	enQueueMsg_BackendSystemStartAutoGetTemperature,
	enQueueMsg_BackendSystemStopAutoGetTemperature,
	enQueueMsg_BackendSystemTemperatureReadyAutoMode, // inform Backend system that temperature acquisition is done
	//to daq task
	enQueueMsg_DaqWaitForCmd,
	enQueueMsg_DaqConfig,
	enQueueMsg_DaqGetTemperature, // request temperature from daq task
	enQueueMsg_DaqEnableAutoTemperature,
	enQueueMsg_DaqWaitForCycle,
	enQueueMsg_DaqDataReady,
	enQueueMsg_DaqDisableAutoTemperature,
	// to Frontend
	enQueueMsg_FrontendLedStateResponse,
	enQueueMsg_FrontendStartModule,
	enQueueMsg_FrontendUpdateTemperatureAutoMode
}enQueueMsgId_t;

typedef enum _enQueueMsgType_t
{
	enQueueMsgType_NONE = 0,
	enQueueMsgType_float,
	enQueueMsgType_int,
	enQueueMsgType_uInt,
	enQueueMsgType_byte,
	enQueueMsgType_char,
	enQueueMsgType_bit
}enQueueMsgType_t;

typedef union _QUEUE_MSG_PAYLOAD_T
{
	float f[QUEUE_MSG_MAX_LENGTH_FLOAT];
	int16_t i16[QUEUE_MSG_MAX_LENGTH_UINT16];
	uint16_t ui16[QUEUE_MSG_MAX_LENGTH_UINT16];
	int8_t i8[QUEUE_MSG_MAX_LENGTH_UINT8];
	uint8_t ui8[QUEUE_MSG_MAX_LENGTH_UINT8];
}QUEUE_MSG_PAYLOAD_T;

typedef struct _xQueueMsgFormat_t
{
	enModuleId_t		enModuleSource;
	enQueueMsgId_t 		enMsgId;
	enQueueMsgType_t 	enMsgType;
	uint8_t 			enMsgLength;
	QUEUE_MSG_PAYLOAD_T	enMsgPayload; // we can set the payload length here or set it in the typedef QUEUE_MSG_PAYLOAD_T itself, it will effect how to write and read bytes (nested array)
	}xQueueMsgFormat_t;

typedef enum _enLight_t
{
	enLight_Gree,
	enLight_Red
}enLight_t;

extern osMessageQueueId_t xBackendSystemQueueHandle;
extern osMessageQueueId_t xFrontendQueueHandle;
extern osMessageQueueId_t xDaqQueueHandle;

bool bSendQueue(enModuleId_t enModuleSource, enModuleId_t enModuleDestination, enQueueMsgId_t enMsgId, enQueueMsgType_t enMsgType, uint8_t u8MsgLength, void* vPayload);
bool bSendQueueFromIsr(enModuleId_t enModuleSource, enModuleId_t enModuleDestination, enQueueMsgId_t enMsgId, enQueueMsgType_t enMsgType, uint8_t u8MsgLength, void* vPayload);
bool bReceiveQueue(enModuleId_t enModule, xQueueMsgFormat_t* xMsg, uint32_t u32WaitingTime);

#endif /* APPLICATION_USER_COMMONOSFUNCTION_H_ */
