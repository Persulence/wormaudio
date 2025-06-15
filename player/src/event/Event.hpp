#pragma once

#include <memory>

#include "ElementList.hpp"
#include "ParameterList.hpp"
#include "../automation/AutomationTable.hpp"
#include "juce_core/juce_core.h"
#include "../state/StateMachineDefinition.hpp"

import sm;
import parameter;
import element;

namespace event
{
    class EventInstance;

    class Event : public juce::ReferenceCountedObject
    {
        sm::StateMachineDefinition::Ptr definition;
        // Per-event parameters
        ParameterList parameters;

        // Automation registry and mappings
        std::unique_ptr<automation::AutomationTable> automation;

        ElementList elementList;

        struct Private {};

    public:
        using Ptr = juce::ReferenceCountedObjectPtr<Event>;

        Event(Private, std::unique_ptr<automation::AutomationTable> automationTable);

        static Ptr create()
        {
            return new Event(Private{}, std::make_unique<automation::AutomationTable>());
        }

        const sm::StateMachineDefinition::Ptr& getDefinition()
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

        // Defined after EventInstance
        std::shared_ptr<EventInstance> instantiate();
    };
}
