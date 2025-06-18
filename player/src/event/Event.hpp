#pragma once

#include <memory>

#include "juce_data_structures/juce_data_structures.h"

#include "ElementList.hpp"
#include "ParameterList.hpp"
#include "../automation/AutomationTable.hpp"
#include "../state/StateMachineDefinition.hpp"
#include "resource/SharedResource.hpp"

import sm;
import parameter;
import element;

namespace event
{
    class EventInstance;

    class Event : public resource::SharedResource, public std::enable_shared_from_this<Event>
    {
        struct Private {};

    public:
        // using Ptr = juce::ReferenceCountedObjectPtr<Event>;
        using Ptr = std::shared_ptr<Event>;

        Event(Private, std::unique_ptr<automation::AutomationTable> automationTable, const std::string &name);

        static Ptr create()
        {
            return std::make_shared<Event>(Private{}, std::make_unique<automation::AutomationTable>(), "Event");
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

        ElementList& getElements()
        {
            return elementList;
        }

        std::vector<resource::ResourceHandle> getChildResources() override
        {
            return {definition};
        }

        // Defined after EventInstance
        std::shared_ptr<EventInstance> instantiate();

        juce::Value nameValue() { return name; }

    private:
        resource::Handle<sm::StateMachineDefinition> definition;

        // Per-event parameters
        ParameterList parameters;

        // Automation registry and mappings
        std::unique_ptr<automation::AutomationTable> automation;

        ElementList elementList;

        juce::Value name;

    };
}
