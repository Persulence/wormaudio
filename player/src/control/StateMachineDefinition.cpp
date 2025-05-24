#include <vector>

#include "StateMachineDefinition.hpp"

namespace sm
{
    const std::vector <State::Ptr> &sm::StateMachineDefinition::getStates()
    {
        return states;
    }
}