#pragma once

import control;
#include "ConditionPanel.hpp"

namespace ui
{
    class ComparisonConditionPanel : public ConditionPanel
    {
        condition::ComparisonCondition& condition;

    public:
        explicit ComparisonConditionPanel(condition::ComparisonCondition& condition_);

        void paint(juce::Graphics &g) override;
        void mouseDown(const juce::MouseEvent &event) override;
    };
}
