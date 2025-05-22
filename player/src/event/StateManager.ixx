module;

#include <unordered_map>
#include <vector>
#include <memory>

export module event:StateManager;

import control;

namespace event
{
    struct StateEntry;

    struct Transition
    {
        const sm::ConditionList* conditions;
        StateEntry* nextState;
    };

    struct StateEntry
    {
        std::unique_ptr<sm::StateInstance> instance;
        std::vector<Transition> transitions;
    };

    export class StateManager
    {
        StateEntry* currentState = nullptr;
        std::vector<StateEntry> entries;

    public:
        explicit StateManager(const std::vector<sm::State::Ptr>& states)
        {
            // This abomination copies and converts the event graph into another graph.
            // Slightly concerned by the use of raw pointers.

            // Associates all nodes that have been encountered so far with an entry
            std::unordered_map<sm::State*, StateEntry*> map;

            for (const auto& state : states)
            {
                auto& stateEntry = getOrCreateEntry(map, state);

                for (const auto& transition : state->getTransitions())
                {
                    StateEntry& nextStateEntry = getOrCreateEntry(map, transition.nextState);

                    stateEntry.transitions.emplace_back(Transition{&transition.conditions, &nextStateEntry});
                }
            }

            // TODO hmmm
            currentState = &entries.at(0);
        }

        void logicTick(const sm::ParameterLookup& parameters)
        {
            if (currentState != nullptr)
            {
                for (const auto& [conditions, nextState] : currentState->transitions)
                {
                    if (conditions->test(parameters))
                    {
                        currentState = nextState;
                    }
                }
            }
        }

    private:

        StateEntry& getOrCreateEntry(std::unordered_map<sm::State*, StateEntry*>& map, const sm::State::Ptr &state)
        {
            StateEntry* entry;
            if (const auto it = map.find(state.get()); it != map.end())
            {
                entry = it->second;
            }
            else
            {
                entry = &entries.emplace_back(std::make_unique<sm::StateInstance>(state), std::vector<Transition>{});
                map.emplace(state.get(), entry);
            }

            return *entry;
        }

    };
}
