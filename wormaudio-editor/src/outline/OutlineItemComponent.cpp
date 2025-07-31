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

#include "OutlineItemComponent.hpp"

#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    OutlineItemComponent::OutlineItemComponent(juce::TreeViewItem* item_, const std::string &icon, bool editable):
        icon(ImageCache::getFromFile(loadResource(icon))), item(item_)
    {
        addAndMakeVisible(label);

        if (editable)
            label.setEditable(false, true);
        // label.getTextValue().referTo(name.value);
    }

    OutlineItemComponent::OutlineItemComponent(juce::TreeViewItem* item_):
        OutlineItemComponent(item_, "icon/resource.png", true)
    {
        label.setEditable(false, true);

        addAndMakeVisible(label);
    }

    void OutlineItemComponent::paint(juce::Graphics &g)
    {
        if (item->isSelected())
        {
            g.setColour(juce::Colours::darkblue);
            g.fillRect(getLocalBounds());
        }

        if (!icon.isNull())
        {
            g.drawImage(icon, iconBounds.toFloat(), RectanglePlacement::fillDestination, false);
        }
    }

    void OutlineItemComponent::resized()
    {
        auto bounds = getLocalBounds();
        iconBounds = bounds.removeFromLeft(getHeight()).reduced(4, 4);


        label.setBounds(bounds);
    }

    void OutlineItemComponent::rename()
    {
        if (label.isEditable())
            label.showEditor();
    }
}
