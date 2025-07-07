#pragma once

#include "property/PropertyFiller.hpp"
#include "widget/SliderWidget.hpp"

namespace ui
{
    class EventDefFiller : public PropertyFiller, util::Data<std::string>::Listener
    {
    public:
        explicit EventDefFiller(resource::Handle<event::EventDef> eventDef_):
            eventDef(std::move(eventDef_))
        {
            eventDef->nameValue().setupListener(this, [this](auto&){ refresh(); });
        }

        void initProperties() override;

    private:
        resource::Handle<event::EventDef> eventDef;

        SliderWidget::C::Listener falloffListener;
    };
}
