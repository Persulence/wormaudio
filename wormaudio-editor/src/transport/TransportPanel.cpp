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

#include "TransportPanel.hpp"

namespace ui
{
    void TransportPanel::resized()
    {
        using namespace juce;

        auto bounds = getLocalBounds();
        // playButton.setBounds(bounds.removeFromLeft(bounds.getWidth() / 2).reduced(bounds.getHeight() / 4));
        // stopButton.setBounds(bounds.reduced(bounds.getHeight() / 4));
        auto newb = bounds.withLeft(getWidth() / 2);
        // playButton.setBounds(bounds.withTrimmedRight(getWidth() / 2));
        // stopButton.setBounds(100, 0, getWidth() / 2, getHeight());
        // playButton.setBounds(0, 0, getWidth() / 2, getHeight());

        // Grid grid;
        // using Track = Grid::TrackInfo;
        // using Fr = Grid::Fr;
        // using Px = Grid::Px;
        // grid.templateColumns = { Track{Fr{1}}, Track{Fr{1}}};
        // grid.templateRows = { Track{Fr{1}}};
        // grid.items.add(GridItem{playButton});
        // grid.items.add(GridItem{stopButton});
        // grid.performLayout(getBounds());

        FlexBox flexBox;
        flexBox.flexDirection = FlexBox::Direction::row;
        // I can't work out how to centre the components vertically. Changing the parameter below sets their height to 0.
        flexBox.alignItems = FlexBox::AlignItems::stretch;
        flexBox.justifyContent = FlexBox::JustifyContent::center;
        flexBox.alignContent = FlexBox::AlignContent::center;
        float w = 50;
        // flexBox.items.add(FlexItem{playButton}.withFlex(2).withMaxWidth(w).withMaxHeight(w).withWidth(w));
        // flexBox.items.add(FlexItem{stopButton}.withFlex(2).withMaxWidth(w).withMaxHeight(w).withWidth(w));
        flexBox.items.add(FlexItem{playButton}.withFlex(2));
        flexBox.items.add(FlexItem{stopButton}.withFlex(2));
        flexBox.performLayout(getLocalBounds());
    }
}
