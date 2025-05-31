#include "ComparisonConditionPanel.hpp"

namespace ui
{
    ComparisonConditionPanel::ComparisonConditionPanel(condition::ComparisonCondition &condition_):
        condition(condition_)
    {
        bg = juce::Colours::green;
    }

    void ComparisonConditionPanel::paint(juce::Graphics &g)
    {
        ConditionPanel::paint(g);
    }

    void ComparisonConditionPanel::mouseDown(const juce::MouseEvent &event)
    {
        std::cout << "mouse down\n";
    }
}
