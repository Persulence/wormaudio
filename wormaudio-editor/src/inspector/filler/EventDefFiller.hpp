// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "resource/SharedResource.hpp"
#include "event/EventDef.hpp"

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
