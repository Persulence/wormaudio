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
    }

    void ComparisonComboBox::mouseDoubleClick(const juce::MouseEvent &event)
    {
    }
}


