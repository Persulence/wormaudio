#pragma once

#include "panel/Panel.hpp"

import control;

namespace ui
{
    class ConditionPanel : public Panel
    {
        condition::Condition &condition;

    public:
        explicit ConditionPanel(condition::Condition& condition_);
        void paint(juce::Graphics &g) override;

    };
}
