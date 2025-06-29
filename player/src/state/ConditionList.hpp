#pragma once

#include "ConditionList.fwd.hpp"

#include <memory>
#include <variant>
#include <variant>
#include <vector>
#include <variant>

#include "cereal/types/vector.hpp"
#include "cereal/types/variant.hpp"
#include "cereal_optional_nvp.h"

#include "condition/ComparisonCondition.hpp"
#include "condition/Condition.hpp"
#include "condition/QuantiseCondition.hpp"
#include "condition/RandomCondition.hpp"
#include "condition/TimeCondition.hpp"

namespace condition
{
    enum class ConditionBoolOperator
    {
        AND,
        OR
    };

    using Condition = std::variant<
        ComparisonCondition,
        TimeCondition,
        QuantiseCondition,
        RandomCondition
    >;

    class ConditionList
    {
    public:
        std::vector<Condition> conditions;
        ConditionBoolOperator op{ConditionBoolOperator::AND};
        // util::Data<ConditionBoolOperator> op{AND};

        ConditionList() = default;

        void insertCondition(Condition condition);

        [[nodiscard]] player::Sample test(const sm::ParameterLookup& parameters, const event::LogicTickInfo &info) const;

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            ar(CEREAL_NVP(conditions));
            cereal::make_optional_nvp(ar, "operator", op);
        }
    };
}

