// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include <vector>

#include "StateMachineDefinition.hpp"

namespace sm
{
    StateMachineDefinition::StateMachineDefinition():
        start(std::make_shared<StateDef>()),
        end(std::make_shared<StateDef>())
    {
        start->flags.type = START;
        start->setName("START");
        states.push_back(start);

        end->flags.type = END;
        end->setName("END");
        states.push_back(end);
    }

    void StateMachineDefinition::remove(const resource::Handle<StateDef> &state)
    {
        if (auto it = std::ranges::find(states, state); *it)
        {
            // std::cout << "uses " << (*it).use_count() << "\n";

            // Look through all the other states and remove any transitions to this one
            for (auto& otherState : states)
            {
                otherState->removeTransitionTo(state.get());
            }
            states.erase(it);
        }
    }

    const std::vector <resource::Handle<StateDef>> &StateMachineDefinition::getStates()
    {
        return states;
    }

    resource::Handle<StateDef> StateMachineDefinition::getStart()
    {
        return start;
    }
}
