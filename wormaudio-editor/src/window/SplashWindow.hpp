// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
