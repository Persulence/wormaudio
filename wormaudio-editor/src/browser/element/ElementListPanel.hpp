// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include "ElementDragSource.hpp"
#include "../EntryListPanel.hpp"
#include "event/ElementList.hpp"
#include "widget/BaseElementWidget.hpp"

namespace ui
{
    class Entry : public BaseElementWidget, public ElementDragSource
    {
    public:
        explicit Entry(const event::ElementHandle &handle_);
        void paint(juce::Graphics &g) override;

        event::ElementHandle getHandle() override { return handle; }
        void mouseDrag(const juce::MouseEvent &event) override;
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
