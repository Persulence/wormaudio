#pragma once
#include "transition/condition/ConditionPanel.hpp"

namespace ui
{
    class TimeConditionPanel : public ConditionPanel
    {
    public:
        explicit TimeConditionPanel(condition::TimeCondition& condition_):
            condition(condition_)
        {

        }

        void paint(juce::Graphics &g) override;

    private:
        condition::TimeCondition &condition;
    };
}
