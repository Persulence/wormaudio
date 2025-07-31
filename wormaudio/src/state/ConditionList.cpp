// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "ConditionList.hpp"

namespace condition
{

    void ConditionList::insertCondition(Condition condition)
    {
        conditions.push_back(std::move(condition));

        // Hmmmm
        // return *(conditions.end() - 1);
    }

    player::Sample ConditionList::test(const sm::EventParameterLookup &parameters, const event::LogicTickInfo &info, const sm::StateInstance& currentState) const
    {
        player::Sample result = 0;
        for (const auto& condition : conditions)
        {
            auto sample = std::visit([&parameters, &info, &currentState](const auto& cmp)
            {
                return cmp.test(parameters, info, currentState);
            }, condition);

            if (op == ConditionBoolOperator::OR)
            {
                result = std::max(result, sample);
            }
            else if (op == ConditionBoolOperator::AND)
            {
                if (sample == player::NULL_SAMPLE)
                    return player::NULL_SAMPLE;

                result = std::max(result, sample);
            }
        }

        return result;
    }
}
