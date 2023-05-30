#ifndef GETTEMPERATURESCREENPRESENTER_HPP
#define GETTEMPERATURESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GetTemperatureScreenView;

class GetTemperatureScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GetTemperatureScreenPresenter(GetTemperatureScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual void vUpdateTemperature();

    virtual ~GetTemperatureScreenPresenter() {};

private:
    GetTemperatureScreenPresenter();

    GetTemperatureScreenView& view;
};

#endif // GETTEMPERATURESCREENPRESENTER_HPP
