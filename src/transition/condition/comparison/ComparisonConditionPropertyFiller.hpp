#pragma once

#include "ComparisonComboBox.hpp"
#include "../ConditionPropertyFiller.hpp"

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
        explicit ComparisonConditionPropertyFiller(condition::ComparisonCondition& condition_);
        void initProperties() override;

        condition::ComparisonCondition &condition;
    };
}
