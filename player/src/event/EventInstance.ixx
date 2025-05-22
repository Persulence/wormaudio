module;

#include <memory>

export module event:EventInstance;

import control;

namespace event
{
    export class Event;
    using EventPtr = std::shared_ptr<Event>;

    export class EventInstance
    {
        EventPtr parent;
        sm::TransitionTable::Ptr table;
        // sm::NodeInstance currentState;

    public:
        using Ptr = std::shared_ptr<EventInstance>;
    };
}

