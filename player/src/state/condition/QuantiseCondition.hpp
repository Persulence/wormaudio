#pragma once

#include "Condition.hpp"
#include "util/Data.hpp"
#include "util/serialization_util.hpp"

namespace condition
{
    class QuantiseCondition : public ConditionBase<QuantiseCondition>
    {
    public:
        util::Data<player::Seconds> interval{1};
        player::Tempo tempo;

        QuantiseCondition() = default;

        [[nodiscard]] player::Sample testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info) const;

    private:

        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {

        }
    };
}
