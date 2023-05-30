#ifndef TEMPERATURESCREENVIEW_HPP
#define TEMPERATURESCREENVIEW_HPP

#include <gui_generated/temperaturescreen_screen/TemperatureScreenViewBase.hpp>
#include <gui/temperaturescreen_screen/TemperatureScreenPresenter.hpp>

class TemperatureScreenView : public TemperatureScreenViewBase
{
public:
    TemperatureScreenView();
    virtual ~TemperatureScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void vUpdateTemperatureView(float fTemperatureValue);
    virtual void handleTickEvent();
protected:
    int iTickCounter;
};

#endif // TEMPERATURESCREENVIEW_HPP
