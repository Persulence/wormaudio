#include "EventDef.hpp"

#include <memory>

#include "EventInstance.hpp"
#include "automation/AutomationTable.hpp"
#include "state/StateMachineDefinition.hpp"

namespace event
{
    EventDef::EventDef(std::unique_ptr<automation::AutomationTable> automationTable, const std::string &name_):
        definition(std::make_shared<sm::StateMachineDefinition>()),
        automation(std::move(automationTable)),
        elementList(resource::make<ElementList>(automation))
    {
        name = name_;
    }

    std::shared_ptr<EventInstance> EventDef::instantiate()
    {
        return std::make_shared<EventInstance>(shared_from_this());
    }
}
