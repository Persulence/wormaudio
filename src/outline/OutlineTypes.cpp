#include "OutlineTypes.hpp"

#include "OutlineItemComponent.hpp"
#include "SharedResourceOutlineItem.hpp"
#include "event/Event.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    class SoundEventItem : public SharedResourceItem<event::Event>
    {
    public:
        explicit SoundEventItem(const resource::Handle<event::Event> &resource) :
            SharedResourceItem(resource) {}

    private:
        bool mightContainSubItems() override
        {
            return true;
        }

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

        bool mightContainSubItems() override
        {
            return true;
        }

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
    };

#define REG(Type, factory) reg<Type>([](auto handle) { return factory; });

    void OutlineTypeRegistry::regDefaults()
    {
        // registry.reg<event::Event>([](auto handle) { return std::make_unique<SoundEventItem>(handle); });
        REG(event::Event, make_unique<SoundEventItem>(handle); )
        REG(sm::StateMachineDefinition, make_unique<StateMachineDefinitionItem>(handle); )
    }
}
