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
        flexBox.alignItems = FlexBox::AlignItems::stretch;
        flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
        flexBox.alignContent = FlexBox::AlignContent::flexEnd;
        float w = 50;
        flexBox.items.add(FlexItem{playButton}.withMaxWidth(w).withMaxHeight(w).withWidth(w));
        flexBox.items.add(FlexItem{stopButton}.withMaxWidth(w).withMaxHeight(w).withWidth(w));
        flexBox.performLayout(getLocalBounds());
    }
}
