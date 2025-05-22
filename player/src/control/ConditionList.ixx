module;

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <variant>

export module control:Transition;

import :ParameterLookup;
import Parameter;

namespace sm
{
    export template <class T>
    struct ConditionBase
    {
        [[nodiscard]] bool test(const ParameterLookup& pl) const
        {
            return static_cast<const T*>(this)->testImpl(pl);
        }

    private:
        ConditionBase() = default;
        friend T;
    };

    export struct ParameterCondition : ConditionBase<ParameterCondition>
    {
        std::string name;
        ParameterValue value;

        ParameterCondition(std::string&& name, ParameterValue value):
                name(name),
                value(value)
        {

        }

        [[nodiscard]] bool testImpl(const ParameterLookup& pl) const
        {
            std::cout << "testing parameter\n";

            auto current = pl.get(name).value;
            return current > value;
        }
    };

    export struct ThingCondition : ConditionBase<ThingCondition>
    {
        ThingCondition() = default;

        [[nodiscard]] static bool testImpl(const ParameterLookup& pl)
        {
            std::cout << "testing thing\n";
            return false;
        }
    };

    export struct TrueCondition : ConditionBase<TrueCondition>
    {
        TrueCondition() = default;

        [[nodiscard]] static bool testImpl(const ParameterLookup& pl)
        {
            return true;
        }
    };

    template <class... T>
    using Thing = std::variant<T...>;

    export using Condition = Thing<
        ParameterCondition,
        ThingCondition,
        TrueCondition
    >;

    export class ConditionList
    {
        std::vector<Condition> things;

    public:
        ConditionList() = default;

        ConditionList(std::vector<Condition> conditions_):
            things(std::move(conditions_))
        {

        }

        void insertCondition(Condition&& condition)
        {
            things.push_back(condition);
        }

        [[nodiscard]] bool test(const ParameterLookup& parameters) const
        {
            bool result = true;
            for (const auto& thing : things)
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

