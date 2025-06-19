#pragma once
#include "transition/condition/ConditionPanel.hpp"

namespace ui
{
    class TimeConditionPanel : public ConditionPanel
    {
    public:
        explicit TimeConditionPanel(condition::TimeCondition& condition_);

        void paint(juce::Graphics &g) override;

        void resized() override
        {
            label.setBounds(getLocalBounds());
        }

    private:
        condition::TimeCondition &condition;
        juce::Label label;
    };
}
