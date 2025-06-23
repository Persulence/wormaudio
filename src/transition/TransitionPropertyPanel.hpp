#pragma once

#include "ConditionListPropertyFiller.hpp"
#include "panel/Panel.hpp"

namespace sm
{
    class Transition1;
}

namespace ui
{
    class TransitionPropertyPanel : public Panel
    {
        std::shared_ptr<sm::Transition1> transition;
        std::unique_ptr<Component> conditionList;

    public:
        explicit TransitionPropertyPanel(std::shared_ptr<sm::Transition1> transition_);

        void resized() override;
        void paint(juce::Graphics &g) override;
    };
}

