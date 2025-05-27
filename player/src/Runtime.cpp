#include "Runtime.hpp"

namespace runtime
{
    event::EventInstance::Ptr Runtime::instantiate(const event::Event::Ptr &event)
    {
        auto instance = event->instantiate();
        instances.push_back(instance);
        return instance;
    }
}