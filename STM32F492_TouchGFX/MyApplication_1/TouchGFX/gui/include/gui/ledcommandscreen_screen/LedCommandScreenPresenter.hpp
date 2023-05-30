#ifndef LEDCOMMANDSCREENPRESENTER_HPP
#define LEDCOMMANDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class LedCommandScreenView;

class LedCommandScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    LedCommandScreenPresenter(LedCommandScreenView& v);

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

    virtual ~LedCommandScreenPresenter() {};

    void vSetLed(bool bIsBottonToggled);
    virtual void vUpdateLedCmdToggleBotton(bool bIsLedOn);

private:
    LedCommandScreenPresenter();

    LedCommandScreenView& view;
};

#endif // LEDCOMMANDSCREENPRESENTER_HPP
