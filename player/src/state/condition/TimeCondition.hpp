#pragma once
#include "Condition.hpp"

#include "juce_data_structures/juce_data_structures.h"
#include "util/Time.hpp"
#include "util/WrappedValue.hpp"

namespace condition
{
    struct TimePos
    {
        ExplicitValue<player::Seconds> value;
        player::TimeType type;
    };

    class TimeCondition : public ConditionBase<TimeCondition>
    {
    public:
        TimePos time;

        TimeCondition() = default;

        [[nodiscard]] bool testImpl(const sm::ParameterLookup &pl) const;
    };
}
