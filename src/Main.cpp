/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

#include "command/Commands.hpp"
#include "UiMainComponent.hpp"
#include "util/Data.hpp"



//==============================================================================
class juce_testApplication  : public juce::JUCEApplication
{
public:
    //==============================================================================
    juce_testApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        mainWindow.reset (new MainWindow (getApplicationName()));
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

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow : public juce::DocumentWindow
    {
    public:
        explicit MainWindow(const juce::String& name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            addKeyListener(ui::Commands::getInstance().getKeyMappings());

            // The horror
            setUsingNativeTitleBar(true);
            setContentOwned(new ui::UiMainComponent(), true);
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

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        juce::OpenGLContext glContext;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (juce_testApplication)

class Violation
{

};

// int main()
// {
//     // Data d1 = 1;
//     // Data<int>::OnChanged::Listener l;
//     // d1.setupListener(l, [](auto& a){ std::cout << "changed\n"; });
//     // std::cout << *d1 << "\n";
//     // d1 = *d1 + 1;
//     // std::cout << *d1 << "\n";
//
//     using namespace signal_event;
//
//     using Thing = Callback<>;
//     Thing::Signal s1;
//
//     Thing::Listener l;
//
//     auto s2 = std::move(s1);
// }