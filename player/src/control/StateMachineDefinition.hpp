#pragma once

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

        const std::vector<State::Ptr>& getStates();
    };
}
