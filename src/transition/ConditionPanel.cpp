#include "ConditionPanel.hpp"

namespace ui
{
    using namespace juce;

    ConditionPanel::ConditionPanel(condition::Condition& condition_):
        condition(condition_)
    {
        bg = Colours::red;
    }

    void ConditionPanel::paint(Graphics &g)
    {
        paintBackground(g);
    }
}
