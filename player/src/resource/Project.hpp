#pragma once

#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"

#include "SharedResource.hpp"
#include "event/EventDef.hpp"
#include "event/ParameterList.hpp"
#include "util/serialization_util.hpp"

namespace resource
{
    class Project final : public SharedResource
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

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            // TODO: events
            ar(make_nvp("global_parameters", globalParameters));
        }
    };
}
