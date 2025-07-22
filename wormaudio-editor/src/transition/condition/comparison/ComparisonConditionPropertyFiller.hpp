// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "ComparisonComboBox.hpp"
#include "../ConditionPropertyFiller.hpp"
#include "state/condition/ComparisonCondition.hpp"

namespace ui
{
    class ComparisonPropertyWidget : public PropertyMember, juce::ComboBox::Listener
    {
        condition::ComparisonCondition& condition;

        ComparisonComboBox left;
        ComparisonComboBox right;
        ComparisonComboBox op;

        juce::StretchableLayoutManager layout;

    public:
        explicit ComparisonPropertyWidget(condition::ComparisonCondition& condition_);

        int getDesiredHeight() const override
        {
            return settings::browserEntryHeight;
        }

        void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

        void refresh();

        void resized() override;
    };

    class ComparisonConditionPropertyFiller : public ConditionPropertyFiller
    {

    public:
        ComparisonConditionPropertyFiller(condition::ComparisonCondition &condition_, int index);

        void initProperties() override;

        condition::ComparisonCondition &condition;
    };
}
