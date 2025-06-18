#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "resource/SharedResource.hpp"

import sm;

namespace sm
{
    class StateMachineDefinition : public resource::SharedResource
    {
        resource::Handle<StateDef> start;
        resource::Handle<StateDef> end;
        std::vector<resource::Handle<StateDef>> states;

    public:
        StateMachineDefinition();

        template <typename... T>
        void insert(const T&... entries)
        {
            (states.push_back(entries),...);
        }

        void remove(const resource::Handle<StateDef> &state);

        const std::vector<resource::Handle<StateDef>>& getStates();
        resource::Handle<StateDef> getStart();

        std::vector<resource::ResourceHandle> getChildResources() override
        {
            return std::vector<resource::ResourceHandle>{states.begin(), states.end()};
        }
    };
}
