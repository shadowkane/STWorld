/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/splashscreen_screen/SplashScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

SplashScreenViewBase::SplashScreenViewBase() :
    splashScreenInteractionCounter(0)
{
    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_NATURE_LIGHT_LAKE_83477_240X320_ID));
    add(image1);
}

SplashScreenViewBase::~SplashScreenViewBase()
{

}

void SplashScreenViewBase::setupScreen()
{
    transitionBegins();
}

void SplashScreenViewBase::transitionBegins()
{
    //SplashScreenInteraction
    //When screen transition begins delay
    //Delay for 3000 ms (180 Ticks)
    splashScreenInteractionCounter = SPLASHSCREENINTERACTION_DURATION;
}

void SplashScreenViewBase::handleTickEvent()
{
    if (splashScreenInteractionCounter > 0)
    {
        splashScreenInteractionCounter--;
        if (splashScreenInteractionCounter == 0)
        {
                //SplashScreenEnds
                //When SplashScreenInteraction completed change screen to TemperatureScreen
                //Go to TemperatureScreen with block transition
                application().gotoTemperatureScreenScreenBlockTransition();
        }
    }
}