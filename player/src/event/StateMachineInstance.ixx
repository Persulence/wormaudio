module;

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <memory>
#include <ranges>

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

    export class StateMachineInstance
    {
        StateEntry* currentState = nullptr;
        std::vector<std::unique_ptr<StateEntry>> entries;

    public:
        explicit StateMachineInstance(const std::vector<sm::State::Ptr>& states, const sm::State::Ptr &start)
        {
            // TODO: simple handling for single-state instances

            // This abomination copies and converts the event graph into another graph.
            // Slightly concerned by the use of raw pointers.

            // Associates all nodes that have been encountered so far with an entry
            std::unordered_map<sm::State::Ptr, StateEntry*> map;

            for (const auto& state : states)
            {
                auto& stateEntry = getOrCreateEntry(map, state);

                for (const auto &transition: state->getTransitions() | std::views::values)
                {
                    if (auto shared = transition.nextState.lock())
                    {
                        StateEntry& nextStateEntry = getOrCreateEntry(map, shared);

                        stateEntry.transitions.emplace_back(Transition{&transition.conditions, &nextStateEntry});
                    }
                }

                if (state == start)
                {
                    currentState = &stateEntry;
                }
            }

            // Find the start state
            // if (const auto result = std::ranges::find_if(entries,
                // [](auto& e){ return e->instance->parent->flags.startNode; }); *result)

            // {
            //     currentState = result->get();
            // }
        }

        bool logicTick(const sm::ParameterLookup& parameters, element::ElementInstanceContext& context)
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
                if (prevState)
                    prevState->instance->deactivate();

                currentState->instance->activate(context);
                return true;
            }

            return false;
        }

        void stop()
        {
            if (currentState)
            {
                currentState->instance->deactivate();
            }
        }

    private:

        StateEntry& getOrCreateEntry(std::unordered_map<sm::State::Ptr, StateEntry*>& map, sm::State::Ptr state)
        {
            StateEntry* entry;
            if (const auto it = map.find(state); it != map.end())
            {
                entry = it->second;
            }
            else
            {
                entry = entries.emplace_back(std::make_unique<StateEntry>(
                    std::make_unique<sm::StateInstance>(state), std::vector<Transition>{}))
                    .get();

                map.emplace(state, entry);
            }

            return *entry;
        }

    };
}
