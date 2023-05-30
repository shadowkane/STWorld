#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

//static int iTempCounter;

Model::Model() : modelListener(0)
{
	xFrontendSystemStatus.enTemperatureUnit = enTemperatureUnitC;
}

void Model::tick()
{
//	if(iTempCounter>1000)
//	{
//		iTempCounter = 0;
//		modelListener->vUpdateTemperature();
//	}
//	else
//	{
//		iTempCounter++;
//	}

	xFrontendSystemStatus.bRxQueueStatus = bReceiveQueue(enModule_Frontend, &(xFrontendSystemStatus.xMsg), 1);
	if(xFrontendSystemStatus.bRxQueueStatus)
	{
		if(xFrontendSystemStatus.xMsg.enModuleSource == enModule_BackendSystem)
		{
			if(xFrontendSystemStatus.xMsg.enMsgId == enQueueMsg_FrontendLedStateResponse)
			{
				if(xFrontendSystemStatus.xMsg.enMsgPayload.ui8[0] && 0x01)
				{
					modelListener->vUpdateLedCmdToggleBotton(true);
				}
				else
				{
					modelListener->vUpdateLedCmdToggleBotton(false);
				}

			}
			if(xFrontendSystemStatus.xMsg.enMsgId == enQueueMsg_FrontendUpdateTemperatureAutoMode)
			{
				// message type should be float and length is 1
				if((xFrontendSystemStatus.xMsg.enMsgType == enQueueMsgType_float) && (xFrontendSystemStatus.xMsg.enMsgLength == 1))
				{
					modelListener->vUpdateTemperatureValueInAutoMode(xFrontendSystemStatus.xMsg.enMsgPayload.f[0]);
				}
			}
		}
	}

}

void Model::vUserToggleLed(bool bIsTurnLedOn)
{
	uint8_t u8LedState;
	if(bIsTurnLedOn)
	{
		u8LedState = 1;
		bSendQueue(enModule_Frontend, enModule_BackendSystem, enQueueMsg_BackendSystemSetLedState, enQueueMsgType_byte, 1, &u8LedState);
	}
	else
	{
		u8LedState = 0;
		bSendQueue(enModule_Frontend, enModule_BackendSystem, enQueueMsg_BackendSystemSetLedState, enQueueMsgType_byte, 1, &u8LedState);
	}
}

void Model::vRequestLedState()
{
	bSendQueue(enModule_Frontend, enModule_BackendSystem, enQueueMsg_BackendSystemGettLedState, enQueueMsgType_NONE, 0, NULL);
}

void Model::vRequestStartAutoGetTemperature()
{
	bSendQueue(enModule_Frontend, enModule_BackendSystem, enQueueMsg_BackendSystemStartAutoGetTemperature,  enQueueMsgType_NONE, 0, NULL);
}

void Model::vRequestStopAutoGetTemperature()
{
	bSendQueue(enModule_Frontend, enModule_BackendSystem, enQueueMsg_BackendSystemStopAutoGetTemperature,  enQueueMsgType_NONE, 0, NULL);
}
