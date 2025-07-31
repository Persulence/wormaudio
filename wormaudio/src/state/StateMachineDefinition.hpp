// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
