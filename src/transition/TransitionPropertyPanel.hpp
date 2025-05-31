#pragma once

#include "ConditionListPanel.hpp"
#include "panel/Panel.hpp"

import control;

namespace ui
{
    class TransitionPropertyPanel : public Panel
    {
        std::shared_ptr<sm::Transition1> transition;

        ConditionListPanel conditionList;

    public:
        explicit TransitionPropertyPanel(std::shared_ptr<sm::Transition1> transition_);

        void update();

        void resized() override;
        void paint(juce::Graphics &g) override;
    };
}

