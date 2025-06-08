module;

#include <memory>
#include <utility>

#include "AutomationTableInstance.hpp"
#include "EventElementInstancer.hpp"

export module event:EventInstance;

import sm;

import :StateManager;
import :Event;
import ElementInstanceManager;

import transport;

namespace event
{
    export class EventInstance
    {
    protected:
        Event::Ptr parent;
        StateMachineInstance stateManager;

    public:
        using Ptr = std::shared_ptr<EventInstance>;

        player::TransportControl transport;

        automation::AutomationTableInstance automationInstance;

        explicit EventInstance(Event::Ptr parent_):
            parent(std::move(parent_)),
            stateManager(StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart())),
            automationInstance()
        {}

        void logicTick(const sm::ParameterLookup& parameters, player::ElementInstanceManager& context, player::TransportControl& globalTransport)
        {
            if (!transport.stopped())
            {
                EventElementInstancer instancer{context, automationInstance};
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

    EventInstance::Ptr Event::instantiate()
    {
        return std::make_shared<EventInstance>(this);
    }
}

