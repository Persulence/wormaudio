// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "ElementListPanel.hpp"
#include "panel/Panel.hpp"
#include "event/ElementList.hpp"
#include "event/EventDef.hpp"

namespace ui
{
    class ElementBrowserPanel :
        public Panel,
        public juce::DragAndDropTarget,
        public event::ElementList::OnChange::Listener
    {
    public:
        explicit ElementBrowserPanel(resource::Handle<event::EventDef> event_);
        void paint(juce::Graphics &g) override;
        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;

    private:
        void refreshElements();

    public:
        bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override;
        void itemDropped(const SourceDetails &dragSourceDetails) override;

    private:
        ElementListPanel listPanel;
        resource::Handle<event::EventDef> event;
    };
}

