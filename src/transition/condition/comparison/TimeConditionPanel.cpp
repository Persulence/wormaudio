#include "TimeConditionPanel.hpp"

namespace ui
{
    TimeConditionPanel::TimeConditionPanel(condition::TimeCondition &condition_):
        condition(condition_)
    {
        bg = juce::Colours::grey;

        addAndMakeVisible(label);
        label.setEditable(true, true);
        label.getTextValue().referTo(condition.time.value.backing);
    }

    void TimeConditionPanel::paint(juce::Graphics &g)
    {
        // g.setColour(juce::Colours::rebeccapurple);
        // g.fillRect(getLocalBounds());
        paintBackground(g);
    }
}
