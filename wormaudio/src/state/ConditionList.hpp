// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "ConditionList.fwd.hpp"

#include <memory>
#include <variant>
#include <vector>

#include "cereal/types/vector.hpp"
#include "cereal/types/variant.hpp"
#include "cereal_optional_nvp.h"
#include "condition/AllElementsDoneCondition.hpp"

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
        RandomCondition,
        AllElementsDoneCondition
    >;

    class ConditionList
    {
    public:
        std::vector<Condition> conditions;
        ConditionBoolOperator op{ConditionBoolOperator::AND};
        // util::Data<ConditionBoolOperator> op{AND};

        ConditionList() = default;

        void insertCondition(Condition condition);
        void removeCondition();

        [[nodiscard]] player::Sample test(const sm::EventParameterLookup& parameters, const event::LogicTickInfo &info, const sm::StateInstance& currentState) const;

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            ar(CEREAL_NVP(conditions));
            cereal::make_optional_nvp(ar, "operator", op);
        }
    };
}

