#pragma once

#include "panel/Panel.hpp"
#include "state/ConditionList.hpp"

import sm;

namespace ui
{
    class ConditionPanel : public Panel
    {
        // condition::Condition &condition;

    public:
        static std::unique_ptr<ConditionPanel> create(condition::Condition& condition);

        explicit ConditionPanel();
        void paint(juce::Graphics &g) override;
        void mouseDown(const juce::MouseEvent &event) override;

    };
}
