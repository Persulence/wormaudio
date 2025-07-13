// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <memory>
#include <vector>

#include "graph/StateDef.hpp"
#include "resource/SharedResource.hpp"

namespace sm
{
    class StateMachineDefinition : public resource::SharedResource
    {
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

    private:
        resource::Handle<StateDef> start;
        resource::Handle<StateDef> end;
        std::vector<resource::Handle<StateDef>> states;

        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(CEREAL_NVP(start), CEREAL_NVP(end),
                cereal::make_nvp("states", states)
                );
        }
    };
}
