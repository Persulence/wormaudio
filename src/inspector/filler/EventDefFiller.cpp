#include "EventDefFiller.hpp"

#include "panel/ChoicePropertyWidget.hpp"
#include "panel/MyPropertyPanel.hpp"
#include "panel/SliderPropertyWidget.hpp"

namespace ui
{
    void EventDefFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Event: " + eventDef->nameValue().getValue()));

        add(ChoicePropertyWidget<player::Attenuation>::create("Attenuation function",
            {
                {"None", player::Attenuation::LINEAR},
                {"Linear", player::Attenuation::LINEAR},
                {"Inverse Distance", player::Attenuation::INVERSE_DISTANCE}
            },
            &eventDef->properties.attenuation));

        auto& min = add(std::make_unique<EntryPropertyWidget<float>>("Min distance", parse::parseFloat));
        min.setValue(eventDef->properties.minDistance);
        min.listener = [this](auto value)
        {
            eventDef->properties.minDistance = value;
        };

        auto& max = add(std::make_unique<EntryPropertyWidget<float>>("Max distance", parse::parseFloat));
        max.setValue(eventDef->properties.maxDistance);
        max.listener = [this](auto value)
        {
            eventDef->properties.maxDistance = value;
        };

        auto& falloff = add(std::make_unique<SliderPropertyWidget>("Falloff"));
        falloff.slider.setRange(0, 2, 0.01);
        falloff.slider.setValue(eventDef->properties.falloff, false);
        falloff.slider.onChanged.setup(&falloffListener, [this](auto val)
        {
            eventDef->properties.falloff = val;
        });
    }
}
