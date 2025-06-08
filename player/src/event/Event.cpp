module;

#include <memory>
#include "automation/AutomationTable.hpp"
#include "state/StateMachineDefinition.hpp"

module event;

namespace event
{
    Event::Event(Private, std::unique_ptr<automation::AutomationTable> automationTable):
        definition(std::make_shared<sm::StateMachineDefinition>()),
        automation(std::move(automationTable)),
        elementList(*automation)
    {

    }
}
