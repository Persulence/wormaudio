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


