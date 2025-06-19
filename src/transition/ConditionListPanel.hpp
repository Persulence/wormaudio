#pragma once

#include "condition/ConditionPanel.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class ConditionListPanel : public Panel
    {
        condition::ConditionList& conditionList;
        std::vector<std::unique_ptr<ConditionPanel>> conditions;

    public:
        explicit ConditionListPanel(condition::ConditionList& conditionList_);

        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;
        void paint(juce::Graphics &g) override;

        void addCondition(const condition::Condition &condition);
        void refresh();
    };
}
