/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef LEDCOMMANDSCREENVIEWBASE_HPP
#define LEDCOMMANDSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/ledcommandscreen_screen/LedCommandScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/ButtonWithIcon.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class LedCommandScreenViewBase : public touchgfx::View<LedCommandScreenPresenter>
{
public:
    LedCommandScreenViewBase();
    virtual ~LedCommandScreenViewBase();
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void vTBLedCmdClicked()
    {
        // Override and implement this function in LedCommandScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::ScalableImage BackgroudImage;
    touchgfx::ButtonWithIcon bLeftSlide;
    touchgfx::ButtonWithIcon bRightSlide;
    touchgfx::ToggleButton tbCmdLed;
    touchgfx::TextArea textArea1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<LedCommandScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // LEDCOMMANDSCREENVIEWBASE_HPP