// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ElementInspectorFiller.hpp"

#include "panel/MyPropertyPanel.hpp"
#include "panel/SliderPropertyWidget.hpp"
#include "resource/ChoiceElement.hpp"
#include "resource/ClipElement.hpp"

namespace ui
{
    using namespace element;

    namespace element_property_filler
    {
        class ClipImpl : public PropertyFiller
        {
            ClipElement& element;

        public:
            explicit ClipImpl(ClipElement &element):
                element(element)
            {
                setHeader(std::make_unique<SectionHeader>("Clip Element"));
            }

            void initProperties() override
            {
                auto& path = add(std::make_shared<StringPropertyWidget>("Path", util::Data{
                    element.getAsset()->getFile().getFullPathName().toStdString()}));
                path.field.setEditable(false);

                add(std::make_shared<BoolDataPropertyWidget>("Ignore state change", element.ignoreChange));

                add(std::make_shared<BoolDataPropertyWidget>("Loop", element.loop));
            }
        };

        class ChoiceImpl : public PropertyFiller
        {
            ChoiceElement& element;
            SliderWidget::C::Listener randomPitchListener;

        public:
            explicit ChoiceImpl(ChoiceElement &element) :
                element(element)
            {
                setHeader(std::make_unique<SectionHeader>("Choice Element"));
            }

            void initProperties() override
            {
                add(std::make_shared<BoolDataPropertyWidget>("Loop", element.loop));
                add(std::make_shared<BoolDataPropertyWidget>("Ignore state change", element.ignoreChange));
                auto& randomPitch = add(std::make_shared<SliderPropertyWidget>("Random Pitch"));
                randomPitch.slider.setRange(0.f, 0.9f, 0.05);
                randomPitch.slider.setValue(element.pitchRandom.getValue(), false);
                randomPitch.slider.onChanged.setup(&randomPitchListener, [this](auto val)
                {
                    element.pitchRandom = val;
                });
            }
        };
    }

    ElementInspectorFiller::ElementInspectorFiller(event::ElementHandle handle_):
        handle(std::move(handle_))
    {
        ElementInspectorFiller::initProperties();
    }

    void ElementInspectorFiller::initProperties()
    {
        // Urgh
        if (typeid(*handle.ptr) == typeid(ClipElement))
        {
            add(std::make_shared<element_property_filler::ClipImpl>(dynamic_cast<ClipElement&>(*handle.ptr)));
        }
        else if (typeid(*handle.ptr) == typeid(ChoiceElement))
        {
            add(std::make_shared<element_property_filler::ChoiceImpl>(dynamic_cast<ChoiceElement&>(*handle.ptr)));
        }
    }
}
