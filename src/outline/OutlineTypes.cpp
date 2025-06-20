#include "OutlineTypes.hpp"

#include "OutlineItemComponent.hpp"
#include "SharedResourceOutlineItem.hpp"
#include "browser/FileDragSource.hpp"
#include "browser/element/ElementDragSource.hpp"
#include "editor/Editor.hpp"
#include "event/Event.hpp"
#include "resource/ChoiceElement.hpp"
#include "resource/ClipElement.hpp"

namespace ui
{
    using namespace juce;
    using namespace resource;

    class SoundEventItem : public SharedResourceItem<event::Event>
    {
    public:
        explicit SoundEventItem(const Handle<event::Event> &resource) :
            SharedResourceItem(resource) {}

        class Comp : public OutlineItemComponent
        {
        public:
            explicit Comp() :
                OutlineItemComponent("icon/sound_event.png") {}

        };

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<Comp>();

            ptr->label.getTextValue().referTo(resource->nameValue());

            return ptr;
        }
    };

    class StateMachineDefinitionItem : public SharedResourceItem<sm::StateMachineDefinition>
    {
    public:
        explicit StateMachineDefinitionItem(const Handle<sm::StateMachineDefinition> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>("icon/folder.png");

            ptr->label.setText("State machine", dontSendNotification);
            ptr->label.setEditable(false, false);

            return ptr;
        }
    };

    class StateDefItem : public SharedResourceItem<sm::StateDef>
    {
    public:
        explicit StateDefItem(const Handle<sm::StateDef> &resource) :
            SharedResourceItem(resource) {}

        bool mightContainSubItems() override
        {
            return false;
        }

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>("icon/state_def.png");

            ptr->label.getTextValue().referTo(resource->name);

            return ptr;
        }
    };

    class ParameterListItem : public SharedResourceItem<event::ParameterList>, public editor::EditorParameterList::Changed::Listener
    {
    public:
        explicit ParameterListItem(const Handle<event::ParameterList> &resource) :
            SharedResourceItem(resource)
        {
            editor::getInstance().getEditorParameters().changed.setup(this, [this]{ refresh(); });
        }

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>("icon/folder.png");
            ptr->label.setText("Global parameters", dontSendNotification);
            return ptr;
        }
    };

    class ParameterDefItem : public SharedResourceItem<parameter::ParameterDef>
    {
    public:
        explicit ParameterDefItem(const Handle<parameter::ParameterDef> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>("icon/parameter.png");
            ptr->label.getTextValue().referTo(resource->getNameAsValue());
            return ptr;
        }

        bool mightContainSubItems() override { return false; }
    };

    class ElementListItem : public SharedResourceItem<event::ElementList>
    {
    public:
        explicit ElementListItem(const Handle<event::ElementList> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>("icon/folder.png", false);
            ptr->label.setText("Elements", dontSendNotification);
            return ptr;
        }

        bool isInterestedInDragSource(const DragAndDropTarget::SourceDetails &dragSourceDetails) override
        {
            return FileDragSource::test(dragSourceDetails);
        }

        void itemDropped(const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex) override
        {
            if (auto source = FileDragSource::test(dragSourceDetails))
            {
                auto asset = asset::createAsset(source->getFile());
                auto handle = resource->reg(std::make_unique<element::ClipElement>(asset));
                refresh();
            }
        }

        bool customComponentUsesTreeViewMouseHandler() const override
        {
            return true;
        }

        void itemClicked(const MouseEvent& event) override
        {
            if (event.mods.isRightButtonDown())
            {
                PopupMenu menu;
                menu.addSectionHeader("Element");
                menu.addItem("New choice element", [this]
                {
                    auto element = std::make_unique<element::ChoiceElement>();
                    resource->reg(std::move(element));
                    refresh();
                });
                menu.showMenuAsync(PopupMenu::Options{});
            }
        }
    };

    class ElementItemComponent : public OutlineItemComponent, public ElementDragSource
    {
    public:
        explicit ElementItemComponent(const Handle<element::Element> &element): OutlineItemComponent("icon/clip.png", false),
            element(element)
        {
            label.setText(element->getName(), dontSendNotification);
            label.addMouseListener(this, false);
        }

        void mouseDown(const MouseEvent &event) override
        {
            constexpr auto offset = Point(30, -30);
            if (const auto container = DragAndDropContainer::findParentDragContainerFor(this))
            {
                container->startDragging( "ELEMENT", this,
                        ScaledImage{},
                        false,
                        &offset,
                        nullptr
                        );
            }
        }

        void mouseDrag(const MouseEvent &event) override
        {
        }

        event::ElementHandle getHandle() override
        {
            return event::ElementHandle{element};
        }

        const Handle<element::Element> &element;
    };

    class ElementItem : public SharedResourceItem<element::Element>
    {
    public:
        explicit ElementItem(const Handle<element::Element> &resource) :
            SharedResourceItem(resource)
        {

        }

        std::unique_ptr<Component> createItemComponent() override
        {
            return std::make_unique<ElementItemComponent>(resource);
        }

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
        explicit ChoiceElementItem(const Handle<element::Element> &resource) :
            ElementItem(resource) {}

        void createChildren() override
        {
            auto choice = std::dynamic_pointer_cast<element::ChoiceElement>(resource);
            auto& clips = choice->getClips();
            for (auto& clip : clips)
            {
                addSubItem(new AssetOutlineItem{clip});
            }
        }

        bool isInterestedInDragSource(const DragAndDropTarget::SourceDetails &dragSourceDetails) override
        {
            return FileDragSource::test(dragSourceDetails);
        }

        void itemDropped(const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex) override
        {
            if (auto source = FileDragSource::test(dragSourceDetails))
            {
                auto choice = std::dynamic_pointer_cast<element::ChoiceElement>(resource);
                choice->addClip(asset::createAsset(source->getFile()));
                refresh(this, true);
            }
        }

        bool mightContainSubItems() override
        {
            return true;
        }
    };

#define REG(Type, factory) reg<Type>([](auto handle) { return factory; });

    void OutlineTypeRegistry::regDefaults()
    {
        // registry.reg<event::Event>([](auto handle) { return std::make_unique<SoundEventItem>(handle); });
        REG(event::Event, make_unique<SoundEventItem>(handle); )
        REG(sm::StateMachineDefinition, make_unique<StateMachineDefinitionItem>(handle); )
        REG(sm::StateDef, make_unique<StateDefItem>(handle); )
        REG(event::ParameterListImpl, make_unique<ParameterListItem>(handle); )
        REG(parameter::ParameterDef, make_unique<ParameterDefItem>(handle); )
        REG(event::ElementList, make_unique<ElementListItem>(handle); )

        REG(element::ClipElement, make_unique<ElementItem>(handle); )
        REG(element::ChoiceElement, make_unique<ChoiceElementItem>(handle); )
    }
}
