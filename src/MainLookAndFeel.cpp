#include "MainLookAndFeel.hpp"

using namespace ui;

MainLookAndFeel::MainLookAndFeel()
{
    using namespace juce;

    Colour fg = Colours::white;
    Colour bg = Colours::grey;
    Colour bgDark = Colours::darkgrey;
    Colour accent = Colours::darkblue;

    setColour(PopupMenu::backgroundColourId, bg);
    setColour(PopupMenu::textColourId, fg);
    setColour(PopupMenu::headerTextColourId, bg);
    setColour(PopupMenu::highlightedBackgroundColourId, accent);
}

void MainLookAndFeel::drawPopupMenuBackground(juce::Graphics &graphics, int width, int height)
{
    LookAndFeel_V4::drawPopupMenuBackground(graphics, width, height);
}
