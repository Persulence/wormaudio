#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class ComparisonComboBox : public juce::ComboBox
    {
    public:
        ComparisonComboBox();
        void paint(juce::Graphics &g) override;
        void mouseDoubleClick(const juce::MouseEvent &event) override;
    };
}

