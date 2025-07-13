// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ComparisonComboBox.hpp"
namespace ui
{
    ComparisonComboBox::ComparisonComboBox()
    {
        setJustificationType(juce::Justification::centred);
    }

    void ComparisonComboBox::paint(juce::Graphics &g)
    {
        ComboBox::paint(g);
        // getLookAndFeel().drawComboBox (g, getWidth(), getHeight(), isButtonDown,
                                       // label->getRight(), 0, getWidth() - label->getRight(), getHeight(),
                                       // *this);

        // if (textWhenNothingSelected.isNotEmpty() && label->getText().isEmpty() && ! label->isBeingEdited())
            // getLookAndFeel().drawComboBoxTextWhenNothingSelected (g, *this, *label);
    }

    void ComparisonComboBox::mouseDoubleClick(const juce::MouseEvent &event)
    {
    }
}


