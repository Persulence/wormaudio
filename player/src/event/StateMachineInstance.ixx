module;

#include <unordered_map>
#include <vector>
#include <memory>

export module event:StateManager;

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

    export class StateMachineInstance
    {
        StateEntry* currentState = nullptr;
        std::vector<std::unique_ptr<StateEntry>> entries;

    public:
        explicit StateMachineInstance(const std::vector<sm::StateDef::Ptr>& states, const sm::StateDef::Ptr &start);

        bool logicTick(const sm::ParameterLookup& parameters, element::ElementInstanceContext& context, player::TransportControl& transport);
        void stop() const;

    private:
        StateEntry& getOrCreateEntry(std::unordered_map<sm::StateDef::Ptr, StateEntry*>& map, sm::StateDef::Ptr state);
    };

}
