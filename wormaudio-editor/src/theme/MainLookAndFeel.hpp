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

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    // struct ElementColours
    // {
    //     juce::Colour fg;
    //     juce::Colour bg;
    //     juce::Colour border;
    // };

    class MainLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        static MainLookAndFeel& getInstance()
        {
            static MainLookAndFeel instance;
            return instance;
        }

        // ElementColours& getColour(Element);

        juce::Typeface::Ptr getTypefaceForFont(const juce::Font &) override;

        void drawPopupMenuBackground(juce::Graphics &, int width, int height) override;
        void drawComboBox(juce::Graphics& g, int width, int height, bool, int, int, int, int, juce::ComboBox& box) override;
        bool areLinesDrawnForTreeView(juce::TreeView &) override;

        void drawDocumentWindowTitleBar(juce::DocumentWindow &, juce::Graphics &, int w, int h, int titleSpaceX, int titleSpaceW, const juce::Image *icon, bool drawTitleTextOnLeft) override;

        void drawMenuBarBackground(juce::Graphics &, int width, int height, bool isMouseOverBar, juce::MenuBarComponent &) override;
        void drawMenuBarItem(juce::Graphics &, int width, int height, int itemIndex, const juce::String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, juce::MenuBarComponent &) override;
        juce::Font getMenuBarFont(juce::MenuBarComponent& bar, int itemIndex, const juce::String& itemText) override;

    private:
        MainLookAndFeel();
    };
}
