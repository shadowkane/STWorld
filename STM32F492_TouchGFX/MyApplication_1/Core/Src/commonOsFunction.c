/*
 * commonOsFunction.c
 *
 *  Created on: May 5, 2023
 *      Author: shado
 */

#include "commonOsFunction.h"
#include <stdio.h>

static bool bPrepareMessage(xQueueMsgFormat_t *pxQueueMsg, enModuleId_t enModuleSource, enQueueMsgId_t enMsgId, enQueueMsgType_t enMsgType, uint8_t u8MsgLength, void* vPayload);

static bool bPrepareMessage(xQueueMsgFormat_t *pxQueueMsg, enModuleId_t enModuleSource, enQueueMsgId_t enMsgId, enQueueMsgType_t enMsgType, uint8_t u8MsgLength, void* vPayload)
{
	bool bRetValue = false;
	uint8_t u8Index;

	pxQueueMsg->enModuleSource = enModuleSource;
	pxQueueMsg->enMsgId = enMsgId;
	pxQueueMsg->enMsgType = enMsgType;
	pxQueueMsg->enMsgLength = u8MsgLength;
	switch(pxQueueMsg->enMsgType)
	{
		case enQueueMsgType_NONE:
			//printf("SendQueue function debug: Msg type None\n");
			pxQueueMsg->enMsgLength = 0; // force msg length to 0 just to avoid problems in case enMsgLength wasn't 0
			bRetValue = true;
			break;
		case enQueueMsgType_float:
			//printf("SendQueue function debug: Msg type Float\n");
			if(pxQueueMsg->enMsgLength <= QUEUE_MSG_MAX_LENGTH_FLOAT)
			{
				for(u8Index=0; u8Index<pxQueueMsg->enMsgLength; u8Index++)
				{
					pxQueueMsg->enMsgPayload.f[u8Index] = ((float*)vPayload)[u8Index];
				}
				bRetValue = true;
			}
			else
			{
				printf("SendQueue function debug: Error Msg length(%d) exceed max(%d)!!\n", pxQueueMsg->enMsgLength, QUEUE_MSG_MAX_LENGTH_FLOAT);
			}
			break;
		case enQueueMsgType_int:
		case enQueueMsgType_uInt:
			//printf("SendQueue function debug: Msg type Int/uInt\n");
			if(pxQueueMsg->enMsgLength <= QUEUE_MSG_MAX_LENGTH_UINT16)
			{
				for(u8Index=0; u8Index<pxQueueMsg->enMsgLength; u8Index++)
				{
					pxQueueMsg->enMsgPayload.ui16[u8Index] = ((uint16_t*)vPayload)[u8Index];
				}
				bRetValue = true;
			}
			else
			{
				printf("SendQueue function debug: Error Msg length(%d) exceed max(%d)!!\n", pxQueueMsg->enMsgLength, QUEUE_MSG_MAX_LENGTH_UINT16);
			}
			break;
		case enQueueMsgType_char:
		case enQueueMsgType_byte:
			//printf("SendQueue function debug: Msg type Char/Byte\n");
			if(pxQueueMsg->enMsgLength <= QUEUE_MSG_MAX_LENGTH_UINT8)
			{
				for(u8Index=0; u8Index<pxQueueMsg->enMsgLength; u8Index++)
				{
					pxQueueMsg->enMsgPayload.ui8[u8Index] = ((uint8_t*)vPayload)[u8Index];
				}
				bRetValue = true;
			}
			else
			{
				printf("SendQueue function debug: Error Msg length(%d) exceed max(%d)!!\n", pxQueueMsg->enMsgLength, QUEUE_MSG_MAX_LENGTH_UINT8);
			}
			break;
//		case enQueueMsgType_bit:
//			for(u8Index=0; u8Index<(pxQueueMsg->enMsgLength/8); u8Index++)
//			{
//				pxQueueMsg->enMsgPayload.ui8[u8Index] = (uint8_t)vPayload[u8Index];
//			}
//			break;
		default:
			//printf("SendQueue function debug: Error Msg type not supported!!\n");
			break;
	}

//	printf("bPrepareMessage MessageQueue:\n"\
//			"		Module Source: %d\n"\
//			"		Msg ID: %d | Msg Type:%d | Msg Length: %d\n",\
//			pxQueueMsg->enModuleSource,\
//			pxQueueMsg->enMsgId, pxQueueMsg->enMsgType, pxQueueMsg->enMsgLength);

	return bRetValue;
}

bool bSendQueue(enModuleId_t enModuleSource, enModuleId_t enModuleDestination, enQueueMsgId_t enMsgId, enQueueMsgType_t enMsgType, uint8_t u8MsgLength, void* vPayload)
{
	bool bRetValue = true;
	osStatus_t xSendResult;
	xQueueMsgFormat_t xQueueMsg;
//	uint8_t u8Index;

//	xQueueMsg.enModuleSource = enModuleSource;
//	xQueueMsg.enMsgId = enMsgId;
//	xQueueMsg.enMsgType = enMsgType;
//	xQueueMsg.enMsgLength = u8MsgLength;

//	printf("SendQueue function:\n"\
//			"		Module Source: %d | Module Destination: %d\n"\
//			"		Msg ID: %d | Msg Type:%d | Msg Length: %d\n",\
//			xQueueMsg.enModuleSource, enModuleDestination,\
//			xQueueMsg.enMsgId, xQueueMsg.enMsgType, xQueueMsg.enMsgLength);

//	switch(xQueueMsg.enMsgType)
//	{
//		case enQueueMsgType_NONE:
//			printf("SendQueue function debug: Msg type None\n");
//			xQueueMsg.enMsgLength = 0; // force msg length to 0 just to avoid problems in case enMsgLength wasn't 0
//			break;
//		case enQueueMsgType_float:
//			printf("SendQueue function debug: Msg type Float\n");
//			if(xQueueMsg.enMsgLength <= QUEUE_MSG_MAX_LENGTH_FLOAT)
//			{
//				for(u8Index=0; u8Index<xQueueMsg.enMsgLength; u8Index++)
//				{
//					xQueueMsg.enMsgPayload.f[u8Index] = ((float*)vPayload)[u8Index];
//				}
//			}
//			else
//			{
//				printf("SendQueue function debug: Error Msg length(%d) exceed max(%d)!!\n", xQueueMsg.enMsgLength, QUEUE_MSG_MAX_LENGTH_FLOAT);
//				bRetValue = false;
//			}
//			break;
//		case enQueueMsgType_int:
//		case enQueueMsgType_uInt:
//			printf("SendQueue function debug: Msg type Int/uInt\n");
//			if(xQueueMsg.enMsgLength <= QUEUE_MSG_MAX_LENGTH_UINT16)
//			{
//				for(u8Index=0; u8Index<xQueueMsg.enMsgLength; u8Index++)
//				{
//					xQueueMsg.enMsgPayload.ui16[u8Index] = ((uint16_t*)vPayload)[u8Index];
//				}
//			}
//			else
//			{
//				printf("SendQueue function debug: Error Msg length(%d) exceed max(%d)!!\n", xQueueMsg.enMsgLength, QUEUE_MSG_MAX_LENGTH_UINT16);
//				bRetValue = false;
//			}
//			break;
//		case enQueueMsgType_char:
//		case enQueueMsgType_byte:
//			printf("SendQueue function debug: Msg type Char/Byte\n");
//			if(xQueueMsg.enMsgLength <= QUEUE_MSG_MAX_LENGTH_UINT8)
//			{
//				for(u8Index=0; u8Index<xQueueMsg.enMsgLength; u8Index++)
//				{
//					xQueueMsg.enMsgPayload.ui8[u8Index] = ((uint8_t*)vPayload)[u8Index];
//				}
//			}
//			else
//			{
//				printf("SendQueue function debug: Error Msg length(%d) exceed max(%d)!!\n", xQueueMsg.enMsgLength, QUEUE_MSG_MAX_LENGTH_UINT8);
//				bRetValue = false;
//			}
//			break;
////		case enQueueMsgType_bit:
////			for(u8Index=0; u8Index<(xQueueMsg.enMsgLength/8); u8Index++)
////			{
////				xQueueMsg.enMsgPayload.ui8[u8Index] = (uint8_t)vPayload[u8Index];
////			}
////			break;
//		default:
//			printf("SendQueue function debug: Error Msg type not supported!!\n");
//			bRetValue = false;
//			break;
//	}
	if(bPrepareMessage(&xQueueMsg, enModuleSource, enMsgId, enMsgType, u8MsgLength, vPayload))
	{
		printf("SendQueue function:\n"\
				"		Module Source: %d | Module Destination: %d\n"\
				"		Msg ID: %d | Msg Type:%d | Msg Length: %d\n",\
				xQueueMsg.enModuleSource, enModuleDestination,\
				xQueueMsg.enMsgId, xQueueMsg.enMsgType, xQueueMsg.enMsgLength);
		switch(enModuleDestination)
		{
			case enModule_BackendSystem:
				printf("SendQueue: Send Queue msg to BackendSystem\n");
				xSendResult = osMessageQueuePut(xBackendSystemQueueHandle, &xQueueMsg, 0, 20);
				break;
			case enModule_Frontend:
				printf("SendQueue: Send Queue msg to Frontend\n");
				xSendResult = osMessageQueuePut(xFrontendQueueHandle, &xQueueMsg, 0, 20);
				break;
			case enModule_Daq:
				printf("SendQueue: Send Queue msg to Daq\n");
				xSendResult = osMessageQueuePut(xDaqQueueHandle, &xQueueMsg, 0, 20);
				break;
			default:
				xSendResult = osError;
				break;
		}
		if(xSendResult == osOK)
		{
			printf("SendQueue function debug: Send Queue msg successfully.\n");
			bRetValue = true;
		}
		else
		{

			printf("SendQueue function debug: Send Queue msg failed(%d)!!\n", xSendResult);
			bRetValue = false;
		}
	}

	return bRetValue;
}

bool bSendQueueFromIsr(enModuleId_t enModuleSource, enModuleId_t enModuleDestination, enQueueMsgId_t enMsgId, enQueueMsgType_t enMsgType, uint8_t u8MsgLength, void* vPayload)
{
	bool bRetValue = true;
	osStatus_t xSendResult;
	xQueueMsgFormat_t xQueueMsg;

	if(bPrepareMessage(&xQueueMsg, enModuleSource, enMsgId, enMsgType, u8MsgLength, vPayload))
	{
//		printf("SendQueue function:\n"\
//				"		Module Source: %d | Module Destination: %d\n"\
//				"		Msg ID: %d | Msg Type:%d | Msg Length: %d\n",\
//				xQueueMsg.enModuleSource, enModuleDestination,\
//				xQueueMsg.enMsgId, xQueueMsg.enMsgType, xQueueMsg.enMsgLength);

		switch(enModuleDestination)
		{
			case enModule_BackendSystem:
				//printf("SendQueue: Send Queue msg to BackendSystem\n");
				xSendResult = osMessageQueuePut(xBackendSystemQueueHandle, &xQueueMsg, 0, 0);
				break;
			case enModule_Frontend:
				//printf("SendQueue: Send Queue msg to Frontend\n");
				xSendResult = osMessageQueuePut(xFrontendQueueHandle, &xQueueMsg, 0, 0);
				break;
			case enModule_Daq:
				//printf("SendQueue: Send Queue msg to Daq\n");
				xSendResult = osMessageQueuePut(xDaqQueueHandle, &xQueueMsg, 0, 0);
				break;
			default:
				xSendResult = osError;
				break;
		}
		if(xSendResult == osOK)
		{
			//printf("SendQueue function debug: Send Queue msg successfully.\n");
			bRetValue = true;
		}
		else
		{

			//printf("SendQueue function debug: Send Queue msg failed(%d)!!\n", xSendResult);
			bRetValue = false;
		}
	}

	return bRetValue;
}

bool bReceiveQueue(enModuleId_t enModule, xQueueMsgFormat_t* xMsg, uint32_t u32WaitingTime)
{
	bool bRetValue;
	osStatus_t  xReceiveResult;

	switch(enModule)
	{
		case enModule_BackendSystem:
			xReceiveResult = osMessageQueueGet(xBackendSystemQueueHandle, xMsg, 0, u32WaitingTime);
			break;
		case enModule_Frontend:
			xReceiveResult = osMessageQueueGet(xFrontendQueueHandle, xMsg, 0, u32WaitingTime);
			break;
		case enModule_Daq:
			xReceiveResult = osMessageQueueGet(xDaqQueueHandle, xMsg, 0, u32WaitingTime);
			break;
		default:
			xReceiveResult = osError;
			break;
	}
	if(xReceiveResult == osOK)
	{
		bRetValue = true;
	}
	else
	{
		bRetValue = false;
	}

	return bRetValue;
}



