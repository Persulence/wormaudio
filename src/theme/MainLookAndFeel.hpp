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
