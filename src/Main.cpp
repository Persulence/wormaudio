/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

#include "command/Commands.hpp"
#include "UiMainComponent.hpp"
#include "util/Data.hpp"
#include "../player/src/instance/spatial.hpp"
#include "theme/MainLookAndFeel.hpp"
#include "scene/SplashMainComponent.hpp"
#include "window/SplashWindow.hpp"


//==============================================================================
class Application : public juce::JUCEApplication
{
public:
    //==============================================================================
    Application() {}

    const juce::String getApplicationName() override { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    //==============================================================================
    void initialise(const juce::String &commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        juce::LookAndFeel::setDefaultLookAndFeel(&ui::MainLookAndFeel::getInstance());
        // mainWindow = std::make_unique<ui::SplashWindow>(getApplicationName());
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted(const juce::String &commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
        explicit MainWindow(const juce::String &name) :
            DocumentWindow(name,
                           ui::MainLookAndFeel::getInstance().findColour(juce::ResizableWindow::backgroundColourId),
                           DocumentWindow::allButtons)
        {
            addKeyListener(ui::Commands::getInstance().getKeyMappings());

            // The horror
            setUsingNativeTitleBar(true);
            setContentNonOwned(&ui::UiMainComponent::getInstance(), true);
            glContext.attachTo(*getTopLevelComponent());

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
#else
            setResizable(true, true);
            // None of this works on a tiling window manager
            centreWithSize(700, 400);
            // getTopLevelComponent()->setBounds(0, 0, 1000, 700);
            // centreWithSize(1000, 800);
            // setBoundsRelative(0, 0, 0.5, 0.5);
#endif

            setVisible(true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
            glContext.detach();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        juce::OpenGLContext glContext;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

private:
    std::unique_ptr<juce::DocumentWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(Application)
