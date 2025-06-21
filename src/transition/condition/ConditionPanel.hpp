#pragma once

#include "property/PropertyFiller.hpp"
#include "state/ConditionList.hpp"

namespace ui
{
    class ConditionPanel : public PropertyFiller
    {
    public:
        static std::unique_ptr<ConditionPanel> create(condition::Condition& condition);

        explicit ConditionPanel();
        // void paint(juce::Graphics &g) override;
        // void mouseDown(const juce::MouseEvent &event) override;
    };
}
