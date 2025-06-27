#pragma once

#include "ConditionList.fwd.hpp"

#include <memory>
#include <vector>
#include <variant>

#include "cereal/types/vector.hpp"
#include "cereal/types/variant.hpp"

#include "condition/ComparisonCondition.hpp"
#include "condition/Condition.hpp"
#include "condition/TimeCondition.hpp"

namespace condition
{
    using Condition = std::variant<
        ComparisonCondition,
        TimeCondition
    >;

    class ConditionList
    {
    public:
        std::vector<Condition> conditions;

        ConditionList() = default;

        Condition& insertCondition(Condition condition);

        [[nodiscard]] player::Sample test(const sm::ParameterLookup& parameters, const event::LogicTickInfo &info) const;

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            ar(conditions);
        }
    };
}

