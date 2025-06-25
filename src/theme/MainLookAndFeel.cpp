#include "MainLookAndFeel.hpp"

using namespace ui;
using namespace juce;

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

    setColour(ComboBox::backgroundColourId, bg);
    setColour(ComboBox::outlineColourId, fg);
    setColour(ComboBox::arrowColourId, fg);
}

void MainLookAndFeel::drawPopupMenuBackground(Graphics &graphics, int width, int height)
{
    LookAndFeel_V4::drawPopupMenuBackground(graphics, width, height);
}

void MainLookAndFeel::drawComboBox(Graphics& g, int width, int height, bool, int, int, int, int, ComboBox& box)
{
    // auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
    // Rectangle boxBounds (0, 0, width, height);

    // g.setColour (box.findColour (ComboBox::backgroundColourId));
    // g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);
    //
    // g.setColour (box.findColour (ComboBox::outlineColourId));
    // g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize, 1.0f);

    Rectangle arrowZone (width - 30, 0, 20, height);
    Path path;
    path.startNewSubPath (static_cast<float>(arrowZone.getX()) + 3.0f, static_cast<float>(arrowZone.getCentreY()) - 2.0f);
    path.lineTo(static_cast<float>(arrowZone.getCentreX()), static_cast<float>(arrowZone.getCentreY()) + 3.0f);
    path.lineTo(static_cast<float>(arrowZone.getRight()) - 3.0f, static_cast<float>(arrowZone.getCentreY()) - 2.0f);

    g.setColour(box.findColour (ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
    g.strokePath(path, PathStrokeType (2.0f));
}

bool MainLookAndFeel::areLinesDrawnForTreeView(TreeView &tree_view)
{
    return true;
}
