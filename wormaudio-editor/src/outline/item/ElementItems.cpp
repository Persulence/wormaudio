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

#include "ElementItems.hpp"

#include "editor/Editor.hpp"

#include "browser/FileDragSource.hpp"
#include "outline/SharedResourceOutlineItem.hpp"
#include "resource/ChoiceElement.hpp"
#include "canvas/InspectorSelectionManager.hpp"
#include "inspector/filler/ElementInspectorFiller.hpp"

namespace ui
{
    using namespace juce;
    using namespace resource;

    class ElementItemComponent : public OutlineItemComponent, public ElementDragSource
    {
    public:
        explicit ElementItemComponent(juce::TreeViewItem *item_, const resource::Handle<element::Element> &element):
            OutlineItemComponent(item_, "icon/clip.png", false),
            element(element)
        {
            label.setText(element->getName(), juce::dontSendNotification);
            label.addMouseListener(this, false);
        }

        void mouseDrag(const MouseEvent &event) override
        {
            if (event.mods.isLeftButtonDown() && !dragging)
            {
                dragging = true;
                constexpr auto offset = Point(30, -30);
                if (const auto container = DragAndDropContainer::findParentDragContainerFor(this))
                {
                    container->startDragging("ELEMENT", this,
                                             ScaledImage{},
                                             false,
                                             &offset,
                                             nullptr
                            );
                }
            }
        }

        void mouseUp(const MouseEvent &event) override
        {
            if (event.mods.isLeftButtonDown())
                dragging = false;
        }

        event::ElementHandle getHandle() override
        {
            return event::ElementHandle{element};
        }

        const Handle<element::Element> &element;
    };

    std::unique_ptr<Component> ElementItem::createItemComponent()
    {
        return std::make_unique<ElementItemComponent>(this, resource);
    }

    bool ElementItem::remove()
    {
        // throw std::logic_error{"Not implemented"};
        editor::getInstance().eraseElement(resource);
        return true;
    }

    void ElementItem::itemSelectionChanged(bool isNowSelected)
    {
        if (const auto manager = findSelectionManager<InspectorSelectionManager>())
        {
            if (isNowSelected)
            {
                auto config = std::make_unique<ElementInspectorFiller>(event::ElementHandle{resource});
                manager->select(SimpleSelectionTarget::of(std::move(config)));
            }
            else
            {
                manager->deselectAll();
            }
        }
    }

    void ChoiceElementItem::createChildren()
    {
        auto choice = std::dynamic_pointer_cast<element::ChoiceElement>(resource);
        auto &clips = choice->getClips();
        for (auto &clip: clips)
        {
            addSubItem(new AssetOutlineItem{clip});
        }
    }

    void ChoiceElementItem::itemDropped(const DragAndDropTarget::SourceDetails &dragSourceDetails,
                                        int insertIndex)
    {
        if (auto source = FileDragSource::test(dragSourceDetails))
        {
            auto choice = std::dynamic_pointer_cast<element::ChoiceElement>(resource);
            choice->addClip(editor::getInstance().createAsset(source->getFile()));
            // choice->addClip(asset::createAsset(source->getFile()));
            // treeHasChanged(); // Doesn't work?
            refresh(this, true);
        }
    }
}
