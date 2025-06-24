#pragma once

#include "condition/ConditionPropertyFiller.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class ConditionListPropertyFiller : public PropertyFiller
    {
        condition::ConditionList& conditionList;

    public:
        explicit ConditionListPropertyFiller(condition::ConditionList& conditionList_);
        void initProperties() override;

        void mouseDown(const juce::MouseEvent &event) override;
        // void paint(juce::Graphics &g) override;

        void addCondition(const condition::Condition &condition);


        // void refresh();
    };
}
