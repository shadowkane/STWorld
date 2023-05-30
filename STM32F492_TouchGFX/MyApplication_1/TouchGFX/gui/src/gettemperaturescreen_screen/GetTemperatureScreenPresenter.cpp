#include <gui/gettemperaturescreen_screen/GetTemperatureScreenView.hpp>
#include <gui/gettemperaturescreen_screen/GetTemperatureScreenPresenter.hpp>

GetTemperatureScreenPresenter::GetTemperatureScreenPresenter(GetTemperatureScreenView& v)
    : view(v)
{

}

void GetTemperatureScreenPresenter::activate()
{

}

void GetTemperatureScreenPresenter::deactivate()
{

}

void GetTemperatureScreenPresenter::vUpdateTemperature()
{
	view.vSetTemperature(21);
}
