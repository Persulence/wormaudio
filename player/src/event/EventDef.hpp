#pragma once

#include <memory>

#include "juce_data_structures/juce_data_structures.h"

#include "ElementList.hpp"
#include "EventProperties.hpp"
#include "ParameterList.hpp"
#include "automation/AutomationTable.hpp"
#include "state/StateMachineDefinition.hpp"
#include "resource/SharedResource.hpp"

namespace event
{
    class EventInstance;

    class EventDef : public resource::SharedResource, public std::enable_shared_from_this<EventDef>
    {
    public:
        EventProperties properties;

        EventDef(std::unique_ptr<automation::AutomationTable> automationTable, const std::string &name);

        static resource::Handle<EventDef> create()
        {
            return std::make_shared<EventDef>( std::make_unique<automation::AutomationTable>(), "Event");
        }

        const resource::Handle<sm::StateMachineDefinition>& getDefinition()
        {
            return definition;
        }

        ParameterList& getParameters()
        {
            return parameters;
        }

        [[nodiscard]] automation::AutomationTable& getAutomation() const
        {
            return *automation;
        }

        ElementList& getElements() const
        {
            return *elementList;
        }

        std::vector<resource::ResourceHandle> getChildResources() override
        {
            return {definition, elementList};
        }

        const EventProperties& getProperties() const
        {
            return properties;
        }

        // Defined after EventInstance
        std::shared_ptr<EventInstance> instantiate();

        util::Data<std::string> nameValue() { return name; }

    private:
        resource::Handle<sm::StateMachineDefinition> definition;

        // Per-event parameters
        ParameterListImpl parameters;

        // Automation registry and mappings
        std::shared_ptr<automation::AutomationTable> automation;

        resource::Handle<ElementList> elementList;

        util::Data<std::string> name;

        PRIVATE_SERIALIZE(EventDef)

        INTERNAL_SERIALIZE
        {
            ar(
                cereal::make_nvp("name", name),
                cereal::make_nvp("definition", definition),
                cereal::make_nvp("parameters", parameters),
                cereal::make_nvp("automation", automation),
                cereal::make_nvp("element_list", elementList)
                );

            cereal::make_optional_nvp(ar, "properties", properties);
        }
    };
}
