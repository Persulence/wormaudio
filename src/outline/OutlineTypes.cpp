#include "OutlineTypes.hpp"

#include "OutlineItemComponent.hpp"
#include "SharedResourceOutlineItem.hpp"
#include "event/Event.hpp"
#include "resource/ChoiceElement.hpp"
#include "resource/ClipElement.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    class SoundEventItem : public SharedResourceItem<event::Event>
    {
    public:
        explicit SoundEventItem(const resource::Handle<event::Event> &resource) :
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
        explicit StateMachineDefinitionItem(const resource::Handle<sm::StateMachineDefinition> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>();

            ptr->label.setText("State machine", dontSendNotification);
            ptr->label.setEditable(false, false);

            return ptr;
        }
    };

    class StateDefItem : public SharedResourceItem<sm::StateDef>
    {
    public:
        explicit StateDefItem(const resource::Handle<sm::StateDef> &resource) :
            SharedResourceItem(resource) {}

        bool mightContainSubItems() override
        {
            return false;
        }

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>();

            ptr->label.getTextValue().referTo(resource->name);

            return ptr;
        }
    };

    class ParameterListItem : public SharedResourceItem<event::ParameterList>
    {
    public:
        explicit ParameterListItem(const resource::Handle<event::ParameterList> &resource) :
            SharedResourceItem(resource) {}

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
        explicit ParameterDefItem(const resource::Handle<parameter::ParameterDef> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>("icon/parameter.png");
            ptr->label.getTextValue().referTo(resource->getNameAsValue());
            return ptr;
        }
    };

    class ElementListItem : public SharedResourceItem<event::ElementList>
    {
    public:
        explicit ElementListItem(const ::resource::Handle<event::ElementList> &resource) :
            SharedResourceItem(resource) {}
    };

    class ElementItem : public SharedResourceItem<element::Element>
    {
    public:
        explicit ElementItem(const ::resource::Handle<element::Element> &resource) :
            SharedResourceItem(resource) {}

        bool mightContainSubItems() override { return false; }
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
        REG(element::ChoiceElement, make_unique<ElementItem>(handle); )
    }
}
