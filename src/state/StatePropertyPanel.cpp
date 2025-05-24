#include "StatePropertyPanel.hpp"

#include "canvas/StateNodeWidget.hpp"

namespace ui
{
    void StatePropertyPanel::paint(juce::Graphics &g)
    {
        if (auto shared = parent.lock())
        {
            g.drawText(shared->getState()->getName(), getLocalBounds(), juce::Justification::centred, true);
        }
    }
}

