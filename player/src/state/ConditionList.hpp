#pragma once

#include "ConditionList.fwd.hpp"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <variant>

#include "condition/ComparisonCondition.hpp"
#include "condition/Condition.hpp"
#include "condition/TimeCondition.hpp"

namespace condition
{
    // struct ThingCondition : ConditionBase<ThingCondition>
    // {
    //     ThingCondition() = default;
    //
    //     [[nodiscard]] static bool testImpl(const sm::ParameterLookup& pl)
    //     {
    //         std::cout << "testing thing\n";
    //         return false;
    //     }
    // };
    //
    // struct TrueCondition : ConditionBase<TrueCondition>
    // {
    //     TrueCondition() = default;
    //
    //     [[nodiscard]] static bool testImpl(const sm::ParameterLookup& pl)
    //     {
    //         return true;
    //     }
    // };

    template <class... T>
    using Thing = std::variant<T...>;

    using Condition = Thing<
        ComparisonCondition,
        TimeCondition
    >;

    class ConditionList
    {
    public:

        std::vector<Condition> conditions;

        ConditionList() = default;

        Condition& insertCondition(Condition condition);

        // const TimeCondition* testTimeConditions(const sm::ParameterLookup& parameters, const event::LogicTickInfo& info) const
        // {
        //     for (const auto& condition : conditions)
        //     {
        //         if (auto timeCondition = std::get_if<TimeCondition>(&condition))
        //         {
        //             if (timeCondition->thisBlock(parameters, info))
        //             {
        //                 return timeCondition;
        //             }
        //         }
        //     }
        //
        //     return nullptr;
        // }

        [[nodiscard]] player::Sample test(const sm::ParameterLookup& parameters, const event::LogicTickInfo &info) const;
    };
}

