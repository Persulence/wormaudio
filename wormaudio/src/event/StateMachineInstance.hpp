// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include "graph/StateDef.hpp"
#include "resource/ElementInstanceContext.hpp"
#include "resource/SharedResource.hpp"
#include "state/ConditionList.hpp"

namespace player {
    class TransportControl;
}

namespace sm
{
    class EventParameterLookup;
    class StateInstance;
}

namespace event
{
    struct LogicTickInfo;
    struct StateEntry;

    struct Transition
    {
        const condition::ConditionList* conditions;
        StateEntry* nextState;
    };

    struct StateEntry
    {
        std::unique_ptr<sm::StateInstance> instance;
        std::vector<Transition> transitions;
    };

    class StateMachineInstance
    {
        StateEntry* currentState = nullptr;
        StateEntry* startState = nullptr;
        std::vector<std::unique_ptr<StateEntry>> entries;

    public:
        sm::OnStateChange::Signal onStateChange;

        explicit StateMachineInstance(const std::vector<resource::Handle<sm::StateDef>>& states, const resource::Handle<sm::StateDef> &start);

        bool logicTick(sm::EventParameterLookup& parameters, element::ElementInstanceContext& context, player::TransportControl& transport,
                       const LogicTickInfo& info);
        void stop() const;

        void restart();

    private:
        StateEntry& getOrCreateEntry(std::unordered_map<resource::Handle<sm::StateDef>, StateEntry*>& map, resource::Handle<sm::StateDef> state);
    };

}
