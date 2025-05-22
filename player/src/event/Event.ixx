module;

#include <memory>

export module event;

export import :EventInstance;
export import :StateManager;

namespace event
{
    export class Event
    {


    public:
        using Ptr = std::shared_ptr<Event>;

        EventInstance::Ptr instantiate()
        {
            return std::make_shared<EventInstance>();
        }
    };
}