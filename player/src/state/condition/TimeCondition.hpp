#pragma once
#include "Condition.hpp"

#include "juce_data_structures/juce_data_structures.h"

namespace condition
{
    struct TimePos
    {
        enum Type
        {
            IN_STATE,
            SINCE_EVENT_START
        };

        juce::Value value;
        Type type;
    };

    class TimeCondition : public ConditionBase<TimeCondition>
    {
    public:
        TimePos time;

        TimeCondition() = default;

        [[nodiscard]] bool testImpl(const sm::ParameterLookup &pl) const;
    };
}
