#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

import sm;

namespace sm
{
    class StateMachineDefinition
    {
        State::Ptr start;
        State::Ptr end;
        std::vector<State::Ptr> states;

    public:
        using Ptr = std::shared_ptr<StateMachineDefinition>;

        StateMachineDefinition();

        template <typename... T>
        void insert(const T&... entries)
        {
            (states.push_back(entries),...);
        }

        void remove(const State::Ptr &state);

        const std::vector<State::Ptr>& getStates();
        State::Ptr getStart();
    };
}
