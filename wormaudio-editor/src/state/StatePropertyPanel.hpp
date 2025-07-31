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

#include <browser/FileDragSource.hpp>
#include <canvas/StateNodeWidget.hpp>
#include <panel/Panel.hpp>

#include "ElementRegionWidget.hpp"
#include "../browser/element/ElementDragSource.hpp"
#include "editor/Editor.hpp"
#include "resource/Asset.hpp"

#include "resource/ClipElement.hpp"

namespace ui
{
    class StateNodeWidget;
}

namespace ui
{
    class StatePropertyPanel : public Panel, public juce::DragAndDropTarget
    {
        std::weak_ptr<StateNodeWidget> parent;
        std::vector<std::shared_ptr<ElementRegionWidget>> elements;

    public:
        explicit StatePropertyPanel(std::weak_ptr<StateNodeWidget> parent_):
            parent(std::move(parent_))
        {
            update();
            bg = juce::Colours::darkgrey;
        }

        void paint(juce::Graphics &g) override;
        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;

        void update();

        bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override
        {
            const auto source = dragSourceDetails.sourceComponent.get();
            return dynamic_cast<FileDragSource*>(source)
                   || dynamic_cast<ElementDragSource*>(source);
        }

        void itemDropped(const SourceDetails &dragSourceDetails) override
        {
            const auto source = dragSourceDetails.sourceComponent.get();
            if (auto other = dynamic_cast<FileDragSource*>(source))
                receiveFile(other->getFile());

            if (auto other = dynamic_cast<ElementDragSource*>(source))
                receiveElement(other->getHandle());
        }

        void receiveFile(const juce::File &file)
        {
            auto asset = editor::getInstance().createAsset(file);
            auto element = std::make_shared<element::ClipElement>(asset);

            const auto event = editor::Editor::getInstance().getEvent();
            const auto handle = event->getElements().reg(std::move(element));
            receiveElement(handle);
        }

        void receiveElement(const event::ElementHandle &handle)
        {
            if (const auto shared = parent.lock())
            {
                shared->getState()->insertElement(handle);

                update();
                resized();
                repaint();
            }
        }

        void removeElement(const resource::Handle<element::Element> &element);
    };
}
