#include "StateMachineInstance.hpp"

#include <memory>
#include <vector>
#include <ranges>
#include <unordered_map>

#include "resource/ElementInstanceContext.hpp"

import sm;
import transport;

namespace event
{
    using namespace sm;
    using namespace resource;

    StateMachineInstance::StateMachineInstance(const std::vector<resource::Handle<sm::StateDef>> &states, const resource::Handle<sm::StateDef> &start)
    {
        // TODO: simple handling for single-state instances

        // This abomination copies and converts the event graph into another graph.
        // Slightly concerned by the use of raw pointers.

        // Associates all nodes that have been encountered so far with an entry
        std::unordered_map<Handle<StateDef>, StateEntry*> map;

        for (const auto& state : states)
        {
            auto& stateEntry = getOrCreateEntry(map, state);

            for (const auto &transition: state->getTransitions() | std::views::values)
            {
                if (auto shared = transition->nextState.lock())
                {
                    StateEntry& nextStateEntry = getOrCreateEntry(map, shared);

                    stateEntry.transitions.emplace_back(Transition{&transition->conditions, &nextStateEntry});
                }
            }

            if (state == start)
            {
                currentState = &stateEntry;
            }
        }
    }

    bool StateMachineInstance::logicTick(const ParameterLookup &parameters, element::ElementInstanceContext &context, player::TransportControl& transport)
    {
        bool transitionOccurred = false;
        auto prevState = currentState;
        if (currentState != nullptr)
        {
            for (const auto& [conditions, nextState] : currentState->transitions)
            {
                if (conditions->test(parameters))
                {
                    currentState = nextState;
                    transitionOccurred = true;
                    // std::cout << "Moving to state " << nextState->instance->getName() << "\n";
                }
            }
        }

        if (currentState != nullptr && transitionOccurred)
        {
            if (prevState)
                prevState->instance->deactivate();

            if (currentState->instance->getFlags().type == sm::END)
            {
                transport.setState(player::STOPPED);
                currentState = nullptr;
                return true;
            }

            currentState->instance->activate(context);
            return true;
        }

        return false;
    }

    void StateMachineInstance::stop() const
    {
        if (currentState)
        {
            currentState->instance->deactivate();
        }
    }

    StateEntry & StateMachineInstance::getOrCreateEntry(std::unordered_map<resource::Handle<sm::StateDef>, StateEntry *> &map,
            Handle<StateDef> state) {
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
}
