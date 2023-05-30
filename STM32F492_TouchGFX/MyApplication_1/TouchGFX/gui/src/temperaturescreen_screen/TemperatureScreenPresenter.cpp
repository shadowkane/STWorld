#include <gui/temperaturescreen_screen/TemperatureScreenView.hpp>
#include <gui/temperaturescreen_screen/TemperatureScreenPresenter.hpp>

TemperatureScreenPresenter::TemperatureScreenPresenter(TemperatureScreenView& v)
    : view(v)
{

}

void TemperatureScreenPresenter::activate()
{
	model->vRequestStartAutoGetTemperature();
}

void TemperatureScreenPresenter::deactivate()
{
	model->vRequestStopAutoGetTemperature();
}

void TemperatureScreenPresenter::vUpdateTemperatureValueInAutoMode(float fTemperatureValue)
{
	view.vUpdateTemperatureView(fTemperatureValue);
}
