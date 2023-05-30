#ifndef LEDCOMMANDSCREENVIEW_HPP
#define LEDCOMMANDSCREENVIEW_HPP

#include <gui_generated/ledcommandscreen_screen/LedCommandScreenViewBase.hpp>
#include <gui/ledcommandscreen_screen/LedCommandScreenPresenter.hpp>

class LedCommandScreenView : public LedCommandScreenViewBase
{
public:
    LedCommandScreenView();
    virtual ~LedCommandScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void vTBLedCmdClicked();

    void vSetLedCmdToggleButtonState(bool bIsButtonPressed);
protected:
};

#endif // LEDCOMMANDSCREENVIEW_HPP
