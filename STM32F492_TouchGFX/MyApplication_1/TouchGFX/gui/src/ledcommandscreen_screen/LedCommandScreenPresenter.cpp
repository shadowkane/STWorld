#include <gui/ledcommandscreen_screen/LedCommandScreenView.hpp>
#include <gui/ledcommandscreen_screen/LedCommandScreenPresenter.hpp>

LedCommandScreenPresenter::LedCommandScreenPresenter(LedCommandScreenView& v)
    : view(v)
{

}

void LedCommandScreenPresenter::activate()
{
	// at the startup of screen, fetch for information through model
	// Led state: model will send request to backend system to get led state (we don't get led state directly since we are using a state machine that accept requests
	model->vRequestLedState();
}

void LedCommandScreenPresenter::deactivate()
{

}

void LedCommandScreenPresenter::vSetLed(bool bIsBottonToggled)
{
	if(bIsBottonToggled)
	{
		model->vUserToggleLed(false);
	}
	else
	{
		model->vUserToggleLed(true);
	}
}

void LedCommandScreenPresenter::vUpdateLedCmdToggleBotton(bool bIsLedOn)
{
	if(bIsLedOn)
	{
		view.vSetLedCmdToggleButtonState(false);
	}
	else
	{
		view.vSetLedCmdToggleButtonState(true);
	}
}
