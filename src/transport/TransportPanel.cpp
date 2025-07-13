// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
