#pragma once
#include "ElementDragSource.hpp"
#include "EntryListPanel.hpp"
#include "event/ElementList.hpp"

namespace ui
{
    class Entry : public juce::Component, public ElementDragSource
    {
    public:
        explicit Entry(event::ElementHandle handle_);
        void paint(juce::Graphics &g) override;

        event::ElementHandle getHandle() override { return handle; }
        void mouseDrag(const juce::MouseEvent &event) override;

        event::ElementHandle handle;
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
