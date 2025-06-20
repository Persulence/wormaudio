#pragma once

#include <memory>
#include <utility>

#include "AutomationTableInstance.hpp"
#include "EventElementInstancer.hpp"

#include "EventDef.hpp"
#include "StateMachineInstance.hpp"
#include "player/transport.hpp"

namespace event
{
    class EventInstance
    {
    protected:
        resource::Handle<EventDef> parent;
        StateMachineInstance stateManager;

    public:
        using Ptr = std::shared_ptr<EventInstance>;

        player::TransportControl transport;

        std::unique_ptr<automation::AutomationTableInstance> automationInstance;

        explicit EventInstance(resource::Handle<EventDef> parent_):
            parent(std::move(parent_)),
            stateManager(StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart())),
            automationInstance(std::make_unique<automation::AutomationTableInstance>(parent->getAutomation()))
        {}

        void logicTick(sm::ParameterLookup &parameters, player::ElementInstanceManager& context, player::TransportControl& globalTransport)
        {
            if (!transport.stopped())
            {
                EventElementInstancer instancer{context, *automationInstance};
                automationInstance->logicTick(parameters, transport);
                stateManager.logicTick(parameters, instancer, transport);
            }
            else
            {
                return;
            }

            if (transport.stopped())
            {
                stop();
            }
        }

        void stop() const
        {
            stateManager.stop();
        }
    };
}

