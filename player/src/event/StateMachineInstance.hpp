#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "resource/SharedResource.hpp"

import sm;
import element;
import transport;

namespace event
{
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
        std::vector<std::unique_ptr<StateEntry>> entries;

    public:
        explicit StateMachineInstance(const std::vector<resource::Handle<sm::StateDef>>& states, const resource::Handle<sm::StateDef> &start);

        bool logicTick(const sm::ParameterLookup& parameters, element::ElementInstanceContext& context, player::TransportControl& transport);
        void stop() const;

    private:
        StateEntry& getOrCreateEntry(std::unordered_map<resource::Handle<sm::StateDef>, StateEntry*>& map, resource::Handle<sm::StateDef> state);
    };

}
