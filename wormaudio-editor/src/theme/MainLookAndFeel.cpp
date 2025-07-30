// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "MainLookAndFeel.hpp"
#include "BinaryData.h"

using namespace ui;
using namespace juce;

MainLookAndFeel::MainLookAndFeel()
{
    using namespace juce;

    setDefaultSansSerifTypefaceName("Liberation Sans");

    Colour fg = Colours::white;
    Colour bg = Colours::grey;
    Colour bgDark = Colours::darkgrey;
    Colour accent = Colours::darkblue;

    auto darkRed = Colour{0xff7e2529};

    setColour(DocumentWindow::backgroundColourId, bgDark);

    setColour(PopupMenu::backgroundColourId, bg);
    setColour(PopupMenu::textColourId, fg);
    setColour(PopupMenu::headerTextColourId, bg);
    setColour(PopupMenu::highlightedBackgroundColourId, accent);

    setColour(ComboBox::backgroundColourId, bg);
    setColour(ComboBox::outlineColourId, fg);
    setColour(ComboBox::arrowColourId, fg);

    setColour(TextButton::buttonColourId, darkRed);
    setColour(TextButton::buttonOnColourId, bgDark);
}

juce::Typeface::Ptr MainLookAndFeel::getTypefaceForFont(const juce::Font &font)
{
    if (font.getStyleFlags() & Font::FontStyleFlags::bold)
    {
        static Typeface::Ptr typeface = Typeface::createSystemTypefaceFor(BinaryData::DejaVuSansBold_ttf, BinaryData::DejaVuSansBold_ttfSize);
        return typeface;
    }
    else
    {
        static Typeface::Ptr typeface = Typeface::createSystemTypefaceFor(BinaryData::DejaVuSans_ttf, BinaryData::DejaVuSans_ttfSize);
        return typeface;
    }
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

void MainLookAndFeel::drawDocumentWindowTitleBar(DocumentWindow &document_window, Graphics &graphics, int w, int h,
        int titleSpaceX, int titleSpaceW, const Image *icon, bool drawTitleTextOnLeft)
{
    LookAndFeel_V4::drawDocumentWindowTitleBar(document_window, graphics, w, h, titleSpaceX, titleSpaceW, icon,
                                               drawTitleTextOnLeft);
}

// MenuBar

void MainLookAndFeel::drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar,
        MenuBarComponent &bar)
{
    // auto colour = bar.findColour(TextButton::buttonColourId).withAlpha(0.4f);
    auto colour = Colour{0xff7e2529};

    Rectangle r{width, height};

    g.setColour(colour.contrasting(0.15f));
    g.fillRect(r.removeFromTop(1));
    g.fillRect(r.removeFromBottom(1));

    g.setGradientFill (ColourGradient::vertical (colour, 0, colour.darker (0.2f), static_cast<float>(height)));
    g.fillRect (r);
}

void MainLookAndFeel::drawMenuBarItem(Graphics &g, int width, int height, int itemIndex, const String &itemText,
        bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &bar)
{
    LookAndFeel_V4::drawMenuBarItem(g, width, height, itemIndex, itemText, isMouseOverItem, isMenuOpen,
                                    isMouseOverBar,
                                    bar);
}

Font MainLookAndFeel::getMenuBarFont(MenuBarComponent &bar, int itemIndex, const String &itemText)
{
    // return withDefaultMetrics (FontOptions (static_cast<float>(bar.getHeight()) * 0.7f));
    return withDefaultMetrics(FontOptions{static_cast<float>(15)});
}
