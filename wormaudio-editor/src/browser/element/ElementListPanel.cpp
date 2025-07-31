// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "ElementListPanel.hpp"

namespace ui
{
    using namespace juce;

    Entry::Entry(const event::ElementHandle &handle_):
        BaseElementWidget(handle_)
    {

    }

    void Entry::paint(Graphics &g)
    {
        float cornerSize = 5;
        float thickness = 2;

        const auto reduced = getLocalBounds().toFloat().reduced(thickness / 2);
        g.setColour(Colours::rebeccapurple);
        g.fillRoundedRectangle(reduced, cornerSize);
        g.setColour(Colours::mediumpurple);
        g.drawRoundedRectangle(reduced, cornerSize, thickness);

        g.setColour(Colours::black);
        g.drawText(handle->getName(), getLocalBounds().withTrimmedLeft(10).toFloat(), Justification::centredLeft, true);
    }

    void Entry::mouseDrag(const MouseEvent &event)
    {
        constexpr auto offset = Point(30, -30);
        if (const auto container = DragAndDropContainer::findParentDragContainerFor(this))
        {
            container->startDragging(
                    "FILE", this,
                    ScaledImage{},
                    // ScaledImage{icon, 2},
                    false,
                    &offset,
                    nullptr
                    );
        }
    }

    ElementListPanel::ElementListPanel()
    {
    }

    void ElementListPanel::resized()
    {
    }

    void ElementListPanel::paint(Graphics &g)
    {
        // g.fillRect(getLocalBounds());
    }

    void ElementListPanel::refresh(const event::ElementList &elements)
    {
        removeAllChildren();
        entries.clear();

        for (auto& element : elements.getElements())
        {
            auto& ptr = entries.emplace_back(std::make_shared<Entry>(element));
            addChildComponent(ptr.get());
        }

        expectedHeight = (entries.size() + entryOffset) * EntryListPanel::getEntryHeight();
        setBounds(getBounds().withHeight(getExpectedHeight()));

        updateVisibilities();
    }
}
