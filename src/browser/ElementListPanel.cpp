#include "ElementListPanel.hpp"

namespace ui
{
    using namespace juce;

    Entry::Entry(event::ElementHandle handle)
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
