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
        explicit ElementBrowserPanel(event::EventDef::Ptr event_);
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
        event::EventDef::Ptr event;
    };
}

