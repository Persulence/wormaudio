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

#pragma once

#include "browser/FileDragSource.hpp"
#include "browser/element/ElementDragSource.hpp"
#include "outline/OutlineItemComponent.hpp"
#include "outline/SharedResourceOutlineItem.hpp"

namespace element {
    class ChoiceElement;
}

namespace ui
{
    class ElementItem : public SharedResourceItem<element::Element>
    {
    public:
        explicit ElementItem(const resource::Handle<element::Element> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<juce::Component> createItemComponent() override;

        bool remove() override;

        bool mightContainSubItems() override { return false; }

        void itemSelectionChanged(bool isNowSelected) override;
    };

    class ChoiceElementItem : public ElementItem
    {
        class ChoiceClipItem : public AssetOutlineItem
        {
        public:
            explicit ChoiceClipItem(const asset::AssetHandle &asset) :
                AssetOutlineItem(asset) {}
        };

    public:
        explicit ChoiceElementItem(const resource::Handle<element::Element> &resource) :
            ElementItem(resource) {}

        void createChildren() override;

        bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
        {
            return FileDragSource::test(dragSourceDetails);
        }

        void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex) override;

        bool mightContainSubItems() override
        {
            return true;
        }
    };
}
