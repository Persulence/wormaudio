// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
