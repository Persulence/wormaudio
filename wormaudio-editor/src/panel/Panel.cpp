// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
