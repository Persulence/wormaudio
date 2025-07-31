// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
