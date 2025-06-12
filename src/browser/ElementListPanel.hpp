#pragma once
#include "EntryListPanel.hpp"

namespace ui
{
    class Entry : public juce::Component
    {
    public:
        void paint(juce::Graphics &g) override;
    };

    class ElementListPanel : public EntryListPanel<Entry>
    {
    public:
        ElementListPanel();

        void resized() override;
        void paint(juce::Graphics &g) override;

    private:
    };
}
