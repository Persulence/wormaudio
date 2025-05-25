#include "Panel.hpp"

using namespace ui;

void Panel::paint(juce::Graphics &g)
{
}

void Panel::paintBackground(juce::Graphics &g) const
{
    g.setColour(bg);
    g.fillRect(getLocalBounds());
}

void Panel::paintBorder(juce::Graphics &g) const
{
    // g.setColour(fg);
    // g.drawRect(getLocalBounds(), 2);
}
