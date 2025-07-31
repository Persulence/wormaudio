// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "StateMachineInstance.hpp"

#include <memory>
#include <vector>
#include <ranges>
#include <unordered_map>

#include "graph/StateDef.hpp"
#include "player/transport.hpp"
#include "resource/ElementInstanceContext.hpp"
#include "event/LogicTickInfo.hpp"

namespace event
{
    using namespace sm;
    using namespace resource;

    StateMachineInstance::StateMachineInstance(const std::vector<Handle<StateDef>> &states, const Handle<StateDef> &start)
    {
        // TODO: simple handling for single-state instances
        // if (states.size() == 3)
        // {
        //     auto transitions = start->getTransitions();
        //     StateEntry* startEntry = entries.emplace_back(std::make_unique<StateEntry>(createNodeInstance(start), start->getTransitions())).get();
        // }

        // This abomination copies and converts the event graph into another graph.
        // Slightly concerned by the use of raw pointers.

        // Associates all nodes that have been encountered so far with an entry
        std::unordered_map<Handle<StateDef>, StateEntry*> map;

        for (const auto& state : states)
        {
            auto& stateEntry = getOrCreateEntry(map, state);

            // for (const auto &transition: state->getTransitions() | std::views::values)
            for (const auto &transition: state->getTransitions())
            {
                if (auto shared = transition->nextState.lock())
                {
                    StateEntry& nextStateEntry = getOrCreateEntry(map, shared);

                    stateEntry.transitions.emplace_back(Transition{transition->conditions.get(), &nextStateEntry});
                }
            }

            if (state == start)
            {
                currentState = &stateEntry;
                startState = &stateEntry;
            }
        }
    }

    bool StateMachineInstance::logicTick(sm::EventParameterLookup& parameters, element::ElementInstanceContext &context, player::TransportControl& transport,
                                         const LogicTickInfo& info)
    {
        bool transitionOccurred = false;
        auto prevState = currentState;
        if (currentState != nullptr)
        {
            for (const auto& [conditions, nextState] : currentState->transitions)
            {
                const player::Sample handoff = conditions->test(parameters, info, *currentState->instance);
                if (handoff != player::NULL_SAMPLE)
                {
                    currentState = nextState;
                    transitionOccurred = true;
                    parameters.resetStateTimer(info.blockBeginSamples + handoff);

                    context.stageHandoff(handoff);
                }
            }
        }

        if (currentState != nullptr && transitionOccurred)
        {
            if (currentState->instance->getFlags().type == sm::END)
            {
                transport.setState(player::STOPPED);
                if (prevState)
                    prevState->instance->deactivateAll();

                currentState = nullptr;
                return true;
            }

            if (prevState)
            {
                currentState->instance->handoff(context, prevState->instance.get());
            }
            else
            {
                currentState->instance->activateAll(context);
            }

            onStateChange.emit(currentState->instance->getParent());
            return true;
        }

        return false;
    }

    void StateMachineInstance::stop() const
    {
        if (currentState)
        {
            currentState->instance->deactivateAll();
        }
    }

    void StateMachineInstance::restart()
    {
        currentState = startState;
    }

    StateEntry& StateMachineInstance::getOrCreateEntry(std::unordered_map<Handle<StateDef>, StateEntry *> &map,
                                                       Handle<StateDef> state)
    {
        StateEntry* entry;
        if (const auto it = map.find(state); it != map.end())
        {
            entry = it->second;
        }
        else
        {
            entry = entries.emplace_back(std::make_unique<StateEntry>(
                            std::make_unique<StateInstance>(state), std::vector<Transition>{}))
                    .get();

            map.emplace(state, entry);
        }

        return *entry;
    }
}
