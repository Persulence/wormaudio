// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

        void addCondition(condition::Condition&& condition);

        void removeConditionFiller(int index);

        // void refresh();
    };
}
