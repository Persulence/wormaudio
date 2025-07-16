// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
