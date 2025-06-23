#pragma once

#include "Condition.hpp"

#include "juce_data_structures/juce_data_structures.h"
#include "util/Time.hpp"
#include "util/WrappedValue.hpp"

namespace event
{
    struct LogicTickInfo;
}

namespace condition
{
    struct TimePos
    {
        ExplicitValue<player::Seconds> value;
        player::TimeType type{player::IN_STATE};
    };

    enum class TimeOperator
    {
        GREATER_EQUAL,
        LESS_EQUAL
    };

    class TimeCondition : public ConditionBase<TimeCondition>
    {
    public:
        TimePos time;
        TimeOperator op{TimeOperator::GREATER_EQUAL};

        TimeCondition() = default;

        [[nodiscard]] player::Sample testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info) const;
    };
}
