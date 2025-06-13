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

    private:
        MainLookAndFeel();
    };
}
