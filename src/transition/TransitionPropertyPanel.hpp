#pragma once

#include "panel/Panel.hpp"

import control;

namespace ui
{
    class TransitionPropertyPanel : public Panel
    {
        std::weak_ptr<sm::Transition1> transition;

    public:
        explicit TransitionPropertyPanel(std::shared_ptr<sm::Transition1> transition_):
            transition(std::move(transition_))
        {
            bg = juce::Colours::black;
        }

        void paint(juce::Graphics &g) override
        {
            paintBackground(g);
        }
    };
}

