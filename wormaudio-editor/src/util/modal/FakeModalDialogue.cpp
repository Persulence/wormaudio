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

#include "FakeModalDialogue.hpp"

#include "panel/BorderPanel.hpp"

namespace ui
{
    using namespace juce;

    FakeModalDialogue::FakeModalDialogue(std::shared_ptr<juce::Component> content_):
        content(std::move(content_))
    {
        dropShadow.radius = 5;
        dropShadow.offset = {0, 0};
        dropShadow.colour = juce::Colours::black;

        addAndMakeVisible(content.get());
    }

    void FakeModalDialogue::paint(juce::Graphics &g)
    {
        // paintBackground(g);
        dropShadow.drawForRectangle(g, content->getBounds());
    }

    void FakeModalDialogue::paintOverChildren(juce::Graphics &g)
    {
        g.setColour(Colours::white);
        Panel::paintBorder(g, content->getBounds(), 1);
    }

    void FakeModalDialogue::resized()
    {
        auto contentBounds = getLocalBounds().withSizeKeepingCentre(getHeight() * 0.7, getHeight() * 0.7);
        content->setBounds(contentBounds);
    }
}
