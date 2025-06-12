#pragma once
#include "EntryListPanel.hpp"
#include "event/ElementList.hpp"

// import event;

namespace ui
{
    class Entry : public juce::Component
    {
    public:
        Entry(event::ElementHandle handle);
        void paint(juce::Graphics &g) override;
    };

    class ElementListPanel : public EntryListPanel<Entry>
    {
    public:
        ElementListPanel();

        void resized() override;
        void paint(juce::Graphics &g) override;

        void refresh(const event::ElementList & elements);

    private:
    };
}
