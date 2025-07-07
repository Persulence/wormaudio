#include "EventDefFiller.hpp"

#include "panel/ChoicePropertyWidget.hpp"
#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    void EventDefFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Event: " + eventDef->nameValue().getValue()));

        add(ChoicePropertyWidget<player::Attenuation>::create("Attenuation function",
            {{"Linear", player::Attenuation::LINEAR}},
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
    }
}
