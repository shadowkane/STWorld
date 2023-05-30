#include <gui/ledcommandscreen_screen/LedCommandScreenView.hpp>

LedCommandScreenView::LedCommandScreenView()
{

}

void LedCommandScreenView::setupScreen()
{
    LedCommandScreenViewBase::setupScreen();
}

void LedCommandScreenView::tearDownScreen()
{
    LedCommandScreenViewBase::tearDownScreen();
}

void LedCommandScreenView::vTBLedCmdClicked()
{
	presenter->vSetLed(tbCmdLed.getState());
}

void LedCommandScreenView::vSetLedCmdToggleButtonState(bool bIsButtonPressed)
{
	tbCmdLed.forceState(bIsButtonPressed);
}
