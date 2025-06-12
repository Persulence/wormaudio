#include "ElementListPanel.hpp"

namespace ui
{
    using namespace juce;

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
        // g.drawText(element->getName(), getLocalBounds().withTrimmedLeft(10).toFloat(), Justification::centredLeft, true);
    }

    ElementListPanel::ElementListPanel()
    {
        entries.push_back(std::make_shared<Entry>());
        entries.push_back(std::make_shared<Entry>());
        entries.push_back(std::make_shared<Entry>());

        expectedHeight = (entries.size() + entryOffset) * EntryListPanel::getEntryHeight();

        for (auto entry : entries)
        {
            addChildComponent(entry.get());
        }
    }

    void ElementListPanel::resized()
    {
    }

    void ElementListPanel::paint(Graphics &g)
    {
        // g.fillRect(getLocalBounds());
    }
}
