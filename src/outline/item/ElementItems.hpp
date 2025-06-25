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

        bool mightContainSubItems() override { return false; }
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
