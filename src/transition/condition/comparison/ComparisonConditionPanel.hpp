#pragma once

#include "ComparisonComboBox.hpp"
#include "../ConditionPanel.hpp"

namespace ui
{
    class ComparisonConditionPanel : public ConditionPanel, public juce::ComboBox::Listener
    {
        condition::ComparisonCondition& condition;

        ComparisonComboBox left;
        ComparisonComboBox right;
        ComparisonComboBox op;

        juce::StretchableLayoutManager layout;

    public:
        explicit ComparisonConditionPanel(condition::ComparisonCondition& condition_);
        void initProperties() override;

        void paint(juce::Graphics &g) override;
        void mouseDown(const juce::MouseEvent &event) override;
        void resized() override;
        void refresh();

        void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

    };
}
