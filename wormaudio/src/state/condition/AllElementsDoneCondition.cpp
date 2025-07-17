// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "AllElementsDoneCondition.hpp"

#include "graph/StateDef.hpp"

namespace condition
{
    player::Sample AllElementsDoneCondition::testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance &currentState) const
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
