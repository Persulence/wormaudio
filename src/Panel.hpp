#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class Panel : public juce::Component
    {
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Panel)

        void paint(juce::Graphics &g) override;

    protected:
        Panel() = default;

        void paintBackground(juce::Graphics &g) const;
        void paintBorder(juce::Graphics &g) const;

        juce::Colour fg{juce::Colours::grey};
        juce::Colour bg{juce::Colours::darkgrey};
    };
}
