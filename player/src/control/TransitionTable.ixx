module;

#include <memory>
#include <vector>

export module control:TransitionTable;

import :Node;
import :Transition;

namespace sm
{
    export class StateMachineDefinition
    {
        std::vector<State::Ptr> states;

    public:
        using Ptr = std::shared_ptr<StateMachineDefinition>;

        template <typename... T>
        void insert(const T&... entries)
        {
            (states.push_back(entries),...);
        }

        const std::vector<State::Ptr>& getStates()
        {
            return states;
        }
    };
}
