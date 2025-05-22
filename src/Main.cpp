/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TestMainComponent.h"

import ResourceTestComponent;

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
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        explicit MainWindow(const juce::String& name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned(new ResourceTestComponent(), true);
            // setContentOwned (new TestMainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
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
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (juce_testApplication)

// import control;
// import ParameterLookup;
// import Element;
// import ElementTypes;
// import Node;
// import ElementInstanceManager;
//
// int main (int argc, char** argv)
// {
//     std::cout << "Something terribly amusing" << std::endl;
//     // S s = {"ooer", 1};
//
// //    ParameterLookup lookup;
// //    sm::Transition transition;
// //    transition.insertCondition(sm::Condition{sm::ParameterCondition("ooer", 123)});
// //    transition.insertCondition(sm::Condition{sm::ThingCondition{}});
// //    bool val = transition.test(lookup);
// //    std::cout << "result: " << val << std::endl;
//
//
//     // player::ElementInstanceManager manager;
//     //
//     // auto file = juce::File{"./fridge=1-stereo.wav"};
//     //
//     // auto element = std::make_shared<element::ClipElement>(file);
//     // auto nodePtr = std::make_shared<sm::Node>();
//     // nodePtr->insertElement(element);
//     // auto ptr = createNodeInstance(nodePtr);
//     // ptr->activate(manager);
// }