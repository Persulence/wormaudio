#pragma once

#include "Condition.hpp"

#include "util/Time.hpp"
#include "util/Data.hpp"

namespace event
{
    struct LogicTickInfo;
}

namespace condition
{
    struct TimePos
    {
        util::Data<player::Seconds> valueSeconds;
        player::TimeType type{player::IN_STATE};

        player::Tempo tempo;
        util::Data<bool> useTempo;

        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(make_nvp("value", valueSeconds));
            ar(make_nvp("type", type));
            ar(make_nvp("useTempo", useTempo));
            ar(make_nvp("tempo", tempo));
        }
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

        [[nodiscard]] player::Sample testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance &currentState) const;

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            ar(time, op);
        }
    };
}
