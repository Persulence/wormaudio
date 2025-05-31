#pragma once
#include "ConditionPanel.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

import control;

namespace ui
{
    class ConditionListPanel : public juce::Component
    {
        condition::ConditionList& conditionList;
        std::vector<std::unique_ptr<ConditionPanel>> conditions;

    public:
        explicit ConditionListPanel(condition::ConditionList& conditionList_);

        void refresh();

        void resized() override;
    };
}
