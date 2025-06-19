#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <variant>

#include "condition/ComparisonCondition.hpp"
#include "condition/Condition.hpp"

import parameter;

namespace condition
{
    struct ThingCondition : ConditionBase<ThingCondition>
    {
        ThingCondition() = default;

        [[nodiscard]] static bool testImpl(const sm::ParameterLookup& pl)
        {
            std::cout << "testing thing\n";
            return false;
        }
    };

    struct TrueCondition : ConditionBase<TrueCondition>
    {
        TrueCondition() = default;

        [[nodiscard]] static bool testImpl(const sm::ParameterLookup& pl)
        {
            return true;
        }
    };

    template <class... T>
    using Thing = std::variant<T...>;

    using Condition = Thing<
        TrueCondition,
        ComparisonCondition,
        ThingCondition
    >;

    class ConditionList
    {
    public:

        std::vector<Condition> conditions;

        ConditionList() = default;

        Condition& insertCondition(Condition condition)
        {
            conditions.push_back(std::move(condition));

            // Hmmmm
            return *(conditions.end() - 1);
        }

        [[nodiscard]] bool test(const sm::ParameterLookup& parameters) const
        {
            bool result = true;
            for (const auto& thing : conditions)
            {
                result &= std::visit([&parameters](const auto& cmp)
                {
                    return cmp.test(parameters);
                }, thing);
            }

            return result;
        }
    };
}

