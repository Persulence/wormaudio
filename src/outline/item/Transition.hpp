#pragma once

#include "graph/StateDef.hpp"
#include "outline/SharedResourceOutlineItem.hpp"

namespace ui
{
    class InspectorSelectionManager;
}

namespace ui::outline
{
    class StateDefItem : public SharedResourceItem<sm::StateDef>
    {
    public:
        explicit StateDefItem(const resource::Handle<sm::StateDef> &resource) :
            SharedResourceItem(resource) {}

        bool mightContainSubItems() override
        {
            return true;
        }

        std::unique_ptr<juce::Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>(this, "icon/state_def.png");

            ptr->label.setData(resource->name);

            return ptr;
        }

        bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;
        void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex) override;
    };

    class TransitionItem : public SharedResourceItem<sm::Transition1>
    {
    public:
        explicit TransitionItem(const resource::Handle<sm::Transition1> &resource) :
            SharedResourceItem(resource)
        {

        }

        bool mightContainSubItems() override
        {
            return false;
        }

        bool customComponentUsesTreeViewMouseHandler() const override
        {
            return true;
        }

        void itemClicked(const juce::MouseEvent& event) override
        {
            setSelected(true, true, juce::sendNotification);
        }

        std::unique_ptr<juce::Component> createItemComponent() override;

        void itemSelectionChanged(bool isNowSelected) override;

    };
}
