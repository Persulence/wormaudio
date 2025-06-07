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
        StateDef::Ptr start;
        StateDef::Ptr end;
        std::vector<StateDef::Ptr> states;

    public:
        using Ptr = std::shared_ptr<StateMachineDefinition>;

        StateMachineDefinition();

        template <typename... T>
        void insert(const T&... entries)
        {
            (states.push_back(entries),...);
        }

        void remove(const StateDef::Ptr &state);

        const std::vector<StateDef::Ptr>& getStates();
        StateDef::Ptr getStart();
    };
}
