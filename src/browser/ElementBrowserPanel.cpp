#include "ElementBrowserPanel.hpp"

ui::ElementBrowserPanel::ElementBrowserPanel()
{
    addAndMakeVisible(listPanel);
}

void ui::ElementBrowserPanel::paint(juce::Graphics &g)
{
    paintBackground(g);
}

void ui::ElementBrowserPanel::resized()
{
    listPanel.setBounds(getLocalBounds().withHeight(listPanel.getExpectedHeight()));
    listPanel.updateVisibilities();
}
