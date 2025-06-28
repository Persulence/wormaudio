#pragma once

#include "Condition.hpp"
#include "util/Data.hpp"
#include "util/serialization_util.hpp"

namespace condition
{
    class QuantiseCondition : public ConditionBase<QuantiseCondition>
    {
    public:
        QuantiseCondition() = default;

        [[nodiscard]] player::Sample testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info) const;

    private:
        player::Tempo tempo;
        util::Data<player::Seconds> interval{1};

        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {

        }
    };
}
