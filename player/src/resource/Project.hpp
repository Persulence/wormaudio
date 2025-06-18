#pragma once
#include "SharedResource.hpp"
#include "event/ParameterList.hpp"

namespace resource
{
    class Project : public SharedResource
    {
    public:
        Handle<event::ParameterListImpl> globalParameters;

        Project()
        {
            globalParameters = resource::make<event::ParameterListImpl>();
        }

        std::vector<ResourceHandle> getChildResources() override
        {
            return {globalParameters};
        }
    };
}
