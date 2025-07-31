// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

