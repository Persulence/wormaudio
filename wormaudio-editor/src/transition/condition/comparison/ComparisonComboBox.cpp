// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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


