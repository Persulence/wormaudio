#pragma once
#include "SharedResource.hpp"
#include "event/Event.hpp"
#include "event/ParameterList.hpp"

namespace resource
{
    class Project : public SharedResource
    {
    public:
        Handle<event::ParameterListImpl> globalParameters;
        std::vector<Handle<event::Event>> events;

        Project()
        {
            globalParameters = resource::make<event::ParameterListImpl>();
        }

        std::vector<ResourceHandle> getChildResources() override
        {
            std::vector<ResourceHandle> result;
            for (auto& event : events)
            {
                result.push_back(event);
            }

            result.push_back(globalParameters);

            return result;
        }

        Handle<event::Event> addEvent(Handle<event::Event> event)
        {
            events.push_back(event);
            return event;
        }
    };
}
