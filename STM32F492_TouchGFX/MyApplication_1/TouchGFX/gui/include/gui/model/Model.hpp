#ifndef MODEL_HPP
#define MODEL_HPP

extern "C"
{
#include "commonOsFunction.h"
#include "global.h"
}

typedef struct _xFrontendSystemStatus_t
{
	// Queue attributes
	uint32_t 						u32StateTimeout; // timeout of waiting for queue
	bool 							bRxQueueStatus;	// the status of the received queue from queue command receive
	xQueueMsgFormat_t				xMsg;
	// Led attributes
	bool 							bLedState;
	enTemperatureUnit_t				enTemperatureUnit;
} xFrontendSystemStatus_t;

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void vUserToggleLed(bool bIsTurnLedOn);
    void vRequestLedState();
    void vRequestStartAutoGetTemperature();
    void vRequestStopAutoGetTemperature();
protected:
    ModelListener* modelListener;
    xFrontendSystemStatus_t xFrontendSystemStatus;

};

#endif // MODEL_HPP
