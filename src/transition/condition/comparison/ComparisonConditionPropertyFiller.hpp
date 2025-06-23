#pragma once

#include "ComparisonComboBox.hpp"
#include "../ConditionPropertyFiller.hpp"

namespace ui
{
    class ComparisonConditionPropertyFiller : public ConditionPropertyFiller, public juce::ComboBox::Listener
    {
        condition::ComparisonCondition& condition;

        ComparisonComboBox left;
        ComparisonComboBox right;
        ComparisonComboBox op;

        juce::StretchableLayoutManager layout;

    public:
        explicit ComparisonConditionPropertyFiller(condition::ComparisonCondition& condition_);
        void initProperties() override;

        int getDesiredHeight() const override;

        void paint(juce::Graphics &g) override;
        void mouseDown(const juce::MouseEvent &event) override;
        void resized() override;
        void refresh();

        void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

    };
}
