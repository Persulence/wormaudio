// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
