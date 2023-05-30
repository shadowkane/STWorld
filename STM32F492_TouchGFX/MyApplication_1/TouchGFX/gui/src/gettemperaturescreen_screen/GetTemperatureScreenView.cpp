#include <gui/gettemperaturescreen_screen/GetTemperatureScreenView.hpp>

GetTemperatureScreenView::GetTemperatureScreenView()
{

}

void GetTemperatureScreenView::setupScreen()
{
    GetTemperatureScreenViewBase::setupScreen();
}

void GetTemperatureScreenView::tearDownScreen()
{
    GetTemperatureScreenViewBase::tearDownScreen();
}

void GetTemperatureScreenView::vSetTemperature(int fTemp)
{
	Unicode::snprintf(L_temperatureBuffer, L_TEMPERATURE_SIZE, "%d", fTemp);
	L_temperature.invalidate();
}

void GetTemperatureScreenView ::handleTickEvent()
{
	iTickCounter++;
	if(iTickCounter>60)
	{
		iTickCounter = 0;
		iTemp++;
		if(iTemp>100)
		{
			iTemp = 0;
		}
		//Unicode::snprintf(L_temperatureBuffer, L_TEMPERATURE_SIZE, "%d", iTemp);
		//L_temperature.invalidate();
	}
}
