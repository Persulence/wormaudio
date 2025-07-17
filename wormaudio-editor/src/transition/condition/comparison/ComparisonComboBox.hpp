// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

