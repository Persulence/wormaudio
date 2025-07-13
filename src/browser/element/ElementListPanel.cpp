// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
