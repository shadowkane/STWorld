#ifndef GETTEMPERATURESCREENVIEW_HPP
#define GETTEMPERATURESCREENVIEW_HPP

#include <gui_generated/gettemperaturescreen_screen/GetTemperatureScreenViewBase.hpp>
#include <gui/gettemperaturescreen_screen/GetTemperatureScreenPresenter.hpp>

class GetTemperatureScreenView : public GetTemperatureScreenViewBase
{
public:
    GetTemperatureScreenView();
    virtual ~GetTemperatureScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void vSetTemperature(int fTemp);
    virtual void handleTickEvent();
protected:
    int iTickCounter;
    int iTemp;
};

#endif // GETTEMPERATURESCREENVIEW_HPP
