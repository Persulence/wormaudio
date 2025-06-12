#pragma once

#include "ElementListPanel.hpp"
#include "../panel/Panel.hpp"
#include "event/ElementList.hpp"

import event;

namespace ui
{
    class ElementBrowserPanel : public Panel, public event::ElementList::OnChange::Listener
    {
    public:
        explicit ElementBrowserPanel(event::Event::Ptr event_);
        void paint(juce::Graphics &g) override;
        void resized() override;

    private:
        void refreshElements();

        ElementListPanel listPanel;
        event::Event::Ptr event;
    };
}

