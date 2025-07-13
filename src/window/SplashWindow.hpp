// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "scene/SplashMainComponent.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "theme/MainLookAndFeel.hpp"

namespace ui
{
    class SplashMainComponent;

    class SplashWindow : public juce::DocumentWindow
    {
    public:
        explicit SplashWindow(const juce::String& name):
            DocumentWindow(name, MainLookAndFeel::getInstance().findColour(backgroundColourId), allButtons),
            mainComponent(std::make_unique<SplashMainComponent>())
        {
            setUsingNativeTitleBar(true);
            setContentNonOwned(mainComponent.get(), true);
            setResizable(true, true);

            // None of this works on a tiling window manager
            centreWithSize(700, 400);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }

        void mouseMove(const juce::MouseEvent &event) override
        {
            DocumentWindow::mouseMove(event);
        }

    private:
        std::unique_ptr<SplashMainComponent> mainComponent;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SplashWindow)
    };
}
