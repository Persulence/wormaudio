module;

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <variant>

export module control:Transition;

import :ParameterLookup;
import :Condition;
import Parameter;

import :ComparisonCondition;

namespace condition
{

    export struct ThingCondition : condition::ConditionBase<ThingCondition>
    {
        ThingCondition() = default;

        [[nodiscard]] static bool testImpl(const sm::ParameterLookup& pl)
        {
            std::cout << "testing thing\n";
            return false;
        }
    };

    export struct TrueCondition : condition::ConditionBase<TrueCondition>
    {
        TrueCondition() = default;

        [[nodiscard]] static bool testImpl(const sm::ParameterLookup& pl)
        {
            return true;
        }
    };

    template <class... T>
    using Thing = std::variant<T...>;

    export using Condition = Thing<
        TrueCondition,
        ComparisonCondition,
        ThingCondition
    >;

    export class ConditionList
    {
    public:

        std::vector<Condition> conditions;

        ConditionList() = default;

        void insertCondition(Condition condition)
        {
            conditions.push_back(std::move(condition));
        }

        [[nodiscard]] bool test(const sm::ParameterLookup& parameters) const
        {
            bool result = true;
            for (const auto& thing : conditions)
            {
                result |= std::visit([&parameters](const auto& cmp)
                {
                    return cmp.test(parameters);
                }, thing);
            }

            return result;
        }
    };
}

