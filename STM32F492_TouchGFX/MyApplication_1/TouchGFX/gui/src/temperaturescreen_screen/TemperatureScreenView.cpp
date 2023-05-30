#include <gui/temperaturescreen_screen/TemperatureScreenView.hpp>

TemperatureScreenView::TemperatureScreenView()
{

}

void TemperatureScreenView::setupScreen()
{
    TemperatureScreenViewBase::setupScreen();
}

void TemperatureScreenView::tearDownScreen()
{
    TemperatureScreenViewBase::tearDownScreen();
}

void TemperatureScreenView::handleTickEvent()
{
//	iTickCounter++;
//	if(iTickCounter%60 == 0)
//	{
//		//gauge1.setValue(100);
//
//		gauge1.updateValue(100, 30);
//	}
}

void TemperatureScreenView::vUpdateTemperatureView(float fTemperatureValue)
{
	gauge1.updateValue((int)fTemperatureValue, 5);
	memset(&L_TemperatureBuffer, 0, L_TEMPERATURE_SIZE);
	Unicode::snprintfFloat(L_TemperatureBuffer, L_TEMPERATURE_SIZE, "%.2f°C", fTemperatureValue);
	L_Temperature.invalidate();
}
