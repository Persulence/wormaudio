// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "TransitionPropertyPanel.hpp"

#include "graph/StateDef.hpp"
#include "inspector/InspectorRoot.hpp"

namespace ui
{
    TransitionPropertyPanel::TransitionPropertyPanel(std::shared_ptr<sm::Transition1> transition_):
        transition(std::move(transition_)),
        conditionList(InspectorRoot::wrap(std::make_unique<ConditionListPropertyFiller>(*transition->conditions)))
    {
        addAndMakeVisible(conditionList.get());
    }

    void TransitionPropertyPanel::resized()
    {
        conditionList->setBounds(getLocalBounds());
    }

    void TransitionPropertyPanel::paint(juce::Graphics &g)
    {
        paintBackground(g);
    }
}
