module;

#include <unordered_map>
#include <vector>
#include <memory>

export module event:StateManager;

import control;
import element;

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
        std::vector<std::unique_ptr<StateEntry>> entries;

    public:
        explicit StateManager(const std::vector<sm::State::Ptr>& states)
        {
            // TODO: simple handling for single-state instances

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
            if (!entries.empty())
                currentState = entries.at(0).get();
        }

        void logicTick(const sm::ParameterLookup& parameters, element::ElementInstanceContext& context)
        {
            auto prevState = currentState;
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

            if (currentState != nullptr && currentState != prevState)
            {
                currentState->instance->activate(context);
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
                entry = entries.emplace_back(std::make_unique<StateEntry>(
                    std::make_unique<sm::StateInstance>(state), std::vector<Transition>{}))
                    .get();

                map.emplace(state.get(), entry);
            }

            return *entry;
        }

    };
}
