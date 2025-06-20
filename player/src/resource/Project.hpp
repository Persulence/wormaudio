#pragma once
#include "SharedResource.hpp"
#include "event/EventDef.hpp"
#include "event/ParameterList.hpp"

namespace resource
{
    class Project : public SharedResource
    {
    public:
        Handle<event::ParameterListImpl> globalParameters;
        std::vector<Handle<event::EventDef>> events;

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

        Handle<event::EventDef> addEvent(Handle<event::EventDef> event)
        {
            events.push_back(event);
            return event;
        }
    };
}
