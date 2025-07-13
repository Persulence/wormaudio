// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "Panel.hpp"

using namespace ui;

void Panel::paint(juce::Graphics &g)
{
}

void Panel::paintBackground(juce::Graphics &g) const
{
    g.setColour(bg);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 5);
}

void Panel::paintBorder(juce::Graphics &g) const
{
    // g.setColour(fg);
    // g.drawRect(getLocalBounds(), 2);
    constexpr float borderWidth = 1;
    g.setColour(fg);
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(borderWidth / 2, borderWidth / 2), 5, borderWidth);
}
