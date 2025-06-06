module;

#include <memory>
#include <utility>

export module event:EventInstance;

import sm;

import :StateManager;
import :Event;

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

        explicit EventInstance(Event::Ptr parent_):
            parent(std::move(parent_)),
            stateManager(StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart()))
        {
        }

        void logicTick(const sm::ParameterLookup& parameters, element::ElementInstanceContext& context, player::TransportControl& globalTransport)
        {
            if (!transport.stopped())
            {
                stateManager.logicTick(parameters, context, transport);
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

        void stop()
        {
            stateManager.stop();
        }
    };

    EventInstance::Ptr Event::instantiate()
    {
        return std::make_shared<EventInstance>(this);
    }
}

