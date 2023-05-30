/*
 * daqTask.c
 *
 *  Created on: May 9, 2023
 *      Author: shado
 */

#include "daqTask.h"
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "commonOsFunction.h"
#include "global.h"
#include "Components/Common/temperatureAbstructLayer.h"

typedef enum _enDaqStateMachine_t
{
	enDaqStateMachine_CmdHanlder = 0,
	enDaqStateMachine_GetTemperature,
	enDaqStateMachine_StartAutoTemperature,
	enDaqStateMachine_WaitForCycle,
	enDaqStateMachine_ReadData,
	enDaqStateMachine_StopAutoTemperature,
}enDaqStateMachine_t;

typedef struct _xDaqStatus_t
{
	// State machine attributes
	enDaqStateMachine_t		enDaqStateMachine; // current SM
	// Queue attributes
	uint32_t 				u32StateTimeout; // timeout of waiting for queue
	bool 					bRxQueueStatus;	// the status of the received queue from queue command receive
	xQueueMsgFormat_t		xMsg;
	// Temperature attributes
	bool 					bIsAutoSendTemperatureEnabled;
	enTemperatureUnit_t		enTemperatureUnit;
	int						iAutoSendTemperatureDelay;
} xDaqStatus_t;

xDaqStatus_t xDaqStatus;
static float fTemperatureTmp;
extern TIM_HandleTypeDef htim2;
extern I2C_HandleTypeDef hi2c3;

static void vDaqTaskInit();
static bool bDaqQueueHandler();
static void vDaqStateMachine();
static void vCmdHandler_SmHandler();
static void vGetTemperature_SmHandler();
static void vStartAutoSendTemperature_SmHandler();
static void vWaitingForCycle_SmHandler();
static void vReadData_SmHandler();
static void vStopAutoSendTemperature_SmHandler();

void StartDaqTask(void *argument)
{
	vDaqTaskInit();
	for(;;)
	{
		xDaqStatus.bRxQueueStatus = bReceiveQueue(enModule_Daq, &(xDaqStatus.xMsg), xDaqStatus.u32StateTimeout);
		if(xDaqStatus.bRxQueueStatus)
		{
			if(bDaqQueueHandler())
			{
				vDaqStateMachine();
			}
		}
	}
}

static void vDaqTaskInit()
{
	xDaqStatus.bIsAutoSendTemperatureEnabled = false;
	xDaqStatus.iAutoSendTemperatureDelay = 10000;
	xDaqStatus.enTemperatureUnit = enTemperatureUnitC;
	vTemperatureSensorConfig(&hi2c3);
	bTemperatureSensorInit();
	xDaqStatus.enDaqStateMachine = enDaqStateMachine_CmdHanlder;
	xDaqStatus.u32StateTimeout = osWaitForever; // keep waiting until cmd received
	bSendQueue(enModule_Daq, enModule_BackendSystem, enQueueMsg_BackendSystemInitDone, enQueueMsgType_NONE, 0, NULL); // inform Backend system that daq module initialization is done
}

static bool bDaqQueueHandler()
{
	bool bRetValue = false;

	if(xDaqStatus.enDaqStateMachine == enDaqStateMachine_CmdHanlder)
	{
		// check if msg source is Backend module
		if(xDaqStatus.xMsg.enModuleSource == enModule_BackendSystem)
		{
			if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqConfig)
			{
				bRetValue = true;
			}
			else if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqGetTemperature)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_GetTemperature;
				bRetValue = true;
			}
			else if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqEnableAutoTemperature)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_StartAutoTemperature;
				bRetValue = true;
			}
		}
	}
	else if(xDaqStatus.enDaqStateMachine == enDaqStateMachine_StartAutoTemperature)
	{
		if(xDaqStatus.xMsg.enModuleSource == enModule_Daq)
		{
			if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqWaitForCycle)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_WaitForCycle;
				bRetValue = true;
			}
		}
		if(xDaqStatus.xMsg.enModuleSource == enModule_BackendSystem)
		{
			if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqDisableAutoTemperature)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_StopAutoTemperature;
				bRetValue = true;
			}
		}
	}
	else if(xDaqStatus.enDaqStateMachine == enDaqStateMachine_WaitForCycle)
	{
		if(xDaqStatus.xMsg.enModuleSource == enModule_Daq)
		{
			if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqDataReady)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_ReadData;
				bRetValue = true;
			}
		}
		else if(xDaqStatus.xMsg.enModuleSource == enModule_BackendSystem)
		{
			if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqDisableAutoTemperature)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_StopAutoTemperature;
				bRetValue = true;
			}
		}
	}
	else if(xDaqStatus.enDaqStateMachine == enDaqStateMachine_ReadData)
	{
		if(xDaqStatus.xMsg.enModuleSource == enModule_Daq)
		{
			if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqWaitForCycle)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_WaitForCycle;
				bRetValue = true;
			}
		}
		else if(xDaqStatus.xMsg.enModuleSource == enModule_BackendSystem)
		{
			if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqDisableAutoTemperature)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_StopAutoTemperature;
				bRetValue = true;
			}
		}
	}
	else if(xDaqStatus.enDaqStateMachine == enDaqStateMachine_StopAutoTemperature)
	{
		if(xDaqStatus.xMsg.enModuleSource == enModule_Daq)
		{
			if(xDaqStatus.xMsg.enMsgId == enQueueMsg_DaqWaitForCmd)
			{
				xDaqStatus.enDaqStateMachine = enDaqStateMachine_CmdHanlder;
				bRetValue = true;
			}
		}
	}
	return bRetValue;
}

static void vDaqStateMachine()
{
	switch(xDaqStatus.enDaqStateMachine)
	{
		case enDaqStateMachine_CmdHanlder:
			vCmdHandler_SmHandler();
			break;
		case enDaqStateMachine_GetTemperature:
			vGetTemperature_SmHandler();
			break;
		case enDaqStateMachine_StartAutoTemperature:
			vStartAutoSendTemperature_SmHandler();
			break;
		case enDaqStateMachine_WaitForCycle:
			vWaitingForCycle_SmHandler();
			break;
		case enDaqStateMachine_ReadData:
			vReadData_SmHandler();
			break;
		case enDaqStateMachine_StopAutoTemperature:
			vStopAutoSendTemperature_SmHandler();
			break;
		default:
			break;
	}
}

static void vCmdHandler_SmHandler()
{
	printf("**DaqTask: vCmdHandler_SmHandler**\n");
	xDaqStatus.u32StateTimeout = osWaitForever; // keep waiting until cmd received
}

static void vGetTemperature_SmHandler()
{
	printf("**DaqTask: vGetTemperature_SmHandler**\n");
	fTemperatureTmp++; // virtual temperature
	xDaqStatus.u32StateTimeout = osWaitForever;
	bSendQueue(enModule_Daq, enModule_Daq, enQueueMsg_DaqWaitForCmd, enQueueMsgType_NONE, 0, NULL);
}

static void vStartAutoSendTemperature_SmHandler()
{
	printf("**DaqTask: vStartAutoSendTemperature_SmHandler**\n");
	HAL_TIM_Base_Start_IT(&htim2);
	xDaqStatus.u32StateTimeout = osWaitForever;
	bSendQueue(enModule_Daq, enModule_Daq, enQueueMsg_DaqWaitForCycle, enQueueMsgType_NONE, 0, NULL);
}

static void vWaitingForCycle_SmHandler()
{
	printf("**DaqTask: vWaitingForCycle_SmHandler**\n");
	xDaqStatus.u32StateTimeout = osWaitForever; // keep waiting for queue msg
	// Timer will send queue msg
	// User will disable Auto Temperature
	// in future we can use another alternative beside timer (exemple: timeout = cycle duration)
}

static void vReadData_SmHandler()
{
	printf("**DaqTask: vReadData_SmHandler**\n");
	float fTemperature;

	if(bTemperatureSensorGetTemperature(&fTemperature, xDaqStatus.enTemperatureUnit))
	{
		bSendQueue(enModule_Daq, enModule_BackendSystem, enQueueMsg_BackendSystemTemperatureReadyAutoMode, enQueueMsgType_float, 1, &fTemperature);
	}
	bSendQueue(enModule_Daq, enModule_Daq, enQueueMsg_DaqWaitForCycle, enQueueMsgType_NONE, 0, NULL);
}

static void vStopAutoSendTemperature_SmHandler()
{
	printf("**DaqTask: vStopAutoSendTemperature_SmHandler**\n");
	HAL_TIM_Base_Stop_IT(&htim2);
	xDaqStatus.u32StateTimeout = osWaitForever;
	bSendQueue(enModule_Daq, enModule_Daq, enQueueMsg_DaqWaitForCmd, enQueueMsgType_NONE, 0, NULL);
}
