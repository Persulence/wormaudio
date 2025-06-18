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

#define REG(registry, Type, factory) registry.reg<Type>([](auto handle) { return factory; });

    void regDefaults(OutlineTypeRegistry& registry)
    {
        registry.reg<event::Event>([](auto handle) { return std::make_unique<SoundEventItem>(handle); });
    }
}
