#pragma once

#include "property/PropertyFiller.hpp"
#include "widget/SliderWidget.hpp"

namespace ui
{
    class EventDefFiller : public PropertyFiller, util::Data<std::string>::Listener
    {
    public:
        explicit EventDefFiller(resource::Handle<event::EventDef> eventDef_);

        void initProperties() override;

    private:
        resource::Handle<event::EventDef> eventDef;

        SliderWidget::C::Listener falloffListener;

        std::shared_ptr<juce::Component> attenuationPreview;
    };
}
