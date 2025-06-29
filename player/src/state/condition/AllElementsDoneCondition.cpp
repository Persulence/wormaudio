#include "AllElementsDoneCondition.hpp"

#include "graph/StateDef.hpp"

namespace condition
{
    player::Sample AllElementsDoneCondition::testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance &currentState) const
    {
        for (auto& thing : currentState.getInstances())
        {
            if (!thing->isDone())
                return player::NULL_SAMPLE;
        }

        // TODO: element length introspection rather than block snapping
        return 0;
    }
}
