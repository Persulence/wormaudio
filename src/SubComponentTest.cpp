//
// Created by tom on 19/05/25.
//

#include "SubComponentTest.h"

#include "juce_graphics/fonts/harfbuzz/hb-ot-head-table.hh"

SubComponentTest::SubComponentTest()
{
    header.setColour (juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    header.setButtonText ("Header");
    addAndMakeVisible(header);

    addAndMakeVisible(footer);
    footer.setColour (juce::TextButton::buttonColourId, juce::Colours::cornflowerblue);
    footer.setButtonText ("Footer");

    addAndMakeVisible(sidebar);
    sidebar.setColour (juce::TextButton::buttonColourId, juce::Colours::grey);
    sidebar.setButtonText ("Sidebar");
}

void SubComponentTest::resized()
{
    auto area = getLocalBounds();
    auto headerFooterHeight = 36;
    header.setBounds(area.removeFromTop(headerFooterHeight));
    footer.setBounds(area.removeFromBottom(headerFooterHeight));

    auto sidebarWidth = 80;
    sidebar.setBounds(area.removeFromLeft(sidebarWidth));
}
