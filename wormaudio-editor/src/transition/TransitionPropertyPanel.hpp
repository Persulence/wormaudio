// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

