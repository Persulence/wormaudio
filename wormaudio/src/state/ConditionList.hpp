// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

