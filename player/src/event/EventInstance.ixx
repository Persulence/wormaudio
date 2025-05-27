module;

#include <memory>

export module event:EventInstance;

import control;

import :StateManager;
import :Event;

namespace event
{
    export class EventInstance
    {
        Event::Ptr parent;
        StateManager stateManager;

    public:
        using Ptr = std::shared_ptr<EventInstance>;

        explicit EventInstance(const Event::Ptr &parent_):
            parent(parent_),
            stateManager(StateManager(parent_->getDefinition()->getStates()))
        {
        }

        void logicTick(const sm::ParameterLookup& parameters, element::ElementInstanceContext& context)
        {
            stateManager.logicTick(parameters, context);
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

