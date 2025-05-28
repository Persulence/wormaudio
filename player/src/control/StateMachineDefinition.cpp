#include <vector>

#include "StateMachineDefinition.hpp"

namespace sm
{
    StateMachineDefinition::StateMachineDefinition():
        start(std::make_shared<State>())
    {
        start->flags.initialState = true;
        start->setName("Start");
        states.push_back(start);
    }

    void StateMachineDefinition::remove(const State::Ptr &state) {
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

    const std::vector <State::Ptr> &sm::StateMachineDefinition::getStates()
    {
        return states;
    }

    State::Ptr StateMachineDefinition::getStart()
    {
        return start;
    }
}
