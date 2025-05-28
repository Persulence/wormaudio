#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

import control;

namespace sm
{
    class StateMachineDefinition
    {
        std::vector<State::Ptr> states;

    public:
        using Ptr = std::shared_ptr<StateMachineDefinition>;

        template <typename... T>
        void insert(const T&... entries)
        {
            (states.push_back(entries),...);
        }

        void remove(const State::Ptr &state)
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

        const std::vector<State::Ptr>& getStates();
    };
}
