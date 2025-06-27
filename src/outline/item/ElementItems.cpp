#include "ElementItems.hpp"

#include "browser/FileDragSource.hpp"
#include "outline/SharedResourceOutlineItem.hpp"
#include "resource/ChoiceElement.hpp"

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
            choice->addClip(asset::createAsset(source->getFile()));
            // treeHasChanged(); // Doesn't work?
            refresh(this, true);
        }
    }
}
