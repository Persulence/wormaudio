#include "TransitionPropertyPanel.hpp"

#include "graph/StateDef.hpp"

namespace ui
{
    TransitionPropertyPanel::TransitionPropertyPanel(std::shared_ptr<sm::Transition1> transition_):
        transition(std::move(transition_)),
        conditionList(*transition->conditions)
    {
        // bg = juce::Colours::;
        update();

        addAndMakeVisible(conditionList);
    }

    void TransitionPropertyPanel::update()
    {
        conditionList.refresh();
    }

    void TransitionPropertyPanel::resized()
    {
        conditionList.setBounds(getLocalBounds());
    }

    void TransitionPropertyPanel::paint(juce::Graphics &g)
    {
        paintBackground(g);
    }
}
