// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "Transition.hpp"

#include "canvas/InspectorSelectionManager.hpp"
#include "outline/OutlineItemComponent.hpp"
#include "transition/TransitionPropertyPanel.hpp"
#include "util/selection/SelectionManager.hpp"

namespace ui::outline
{
    using namespace resource;
    using namespace juce;

    class TransitionItemComponent : public OutlineItemComponent
    {
    public:
        TransitionItemComponent(TreeViewItem *item_, const std::string &icon):
            OutlineItemComponent(item_, icon, false)
        {
            label.addMouseListener(this, false);
        }

        void mouseDown(const MouseEvent &event) override
        {
        }

        void mouseDrag(const MouseEvent &event) override
        {
            if (event.mods.isLeftButtonDown() && !dragging)
            {
                dragging = true;
                constexpr auto offset = Point(30, -30);
                if (const auto container = DragAndDropContainer::findParentDragContainerFor(this))
                {
                    container->startDragging("TRANSITION", this,
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
    };

    // bool TransitionItem::isInterestedInDragSource(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    // {
    //     return dynamic_cast<TransitionItem*>(dragSourceDetails.sourceComponent.get());
    // }
    //
    // void TransitionItem::itemDropped(const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex)
    // {
    //     if (auto source = dynamic_cast<TransitionItem*>(dragSourceDetails.sourceComponent.get()))
    //     {
    //     }
    // }

    bool StateDefItem::isInterestedInDragSource(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        return dynamic_cast<TransitionItemComponent*>(dragSourceDetails.sourceComponent.get());
    }

    void StateDefItem::itemDropped(const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex)
    {
        if (auto source = dynamic_cast<TransitionItemComponent*>(dragSourceDetails.sourceComponent.get()))
        {
            if (auto item = dynamic_cast<TransitionItem*>(source->item))
            {
                resource->reorderTransition(item->resource->nextState.lock().get(), insertIndex);
                refresh(this, false);
            }
        }
    }

    std::unique_ptr<Component> TransitionItem::createItemComponent()
    {
        auto ptr = std::make_unique<TransitionItemComponent>(this, "icon/transition.png");

        if (auto shared = resource->nextState.lock())
        {
            auto toName = shared->getName();
            ptr->label.setText("Transition: " + toName, dontSendNotification);
        }
        ptr->label.setEditable(false);

        return ptr;
    }

    void TransitionItem::itemSelectionChanged(bool isNowSelected)
    {
        if (isNowSelected)
        {
            if (const auto manager = findSelectionManager<InspectorSelectionManager>())
            {
                auto config = std::make_unique<TransitionPropertyPanel>(resource);
                manager->select(SimpleSelectionTarget::of(std::move(config)));
            }
        }
        else
        {
            if (const auto manager = findSelectionManager<InspectorSelectionManager>())
                manager->deselectAll();
        }
    }
}
