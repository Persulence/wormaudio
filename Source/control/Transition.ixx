module;

#include <iostream>
#include <string>
#include <vector>
#include <variant>

export module control:Transition;

import ParameterLookup;
import Parameter;

namespace sm
{
    export template <class T>
    struct ConditionBase
    {
        bool test(const ParameterLookup& pl) const
        {
            return static_cast<const T*>(this)->testImpl(pl);
        }
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
        [[nodiscard]] bool testImpl(const ParameterLookup& pl) const
        {
            std::cout << "testing thing\n";
            return false;
        }
    };

    template <class... T>
    using Thing = std::variant<T...>;

    export using Condition = Thing<ConditionBase<ParameterCondition>, ConditionBase<ThingCondition>>;

    export class Transition
    {
        std::vector<Condition> things;

    public:
        void insertCondition(Condition&& condition)
        {
            things.push_back(condition);
        }

        [[nodiscard]] bool test(const ParameterLookup& parameters) const
        {
            for (const auto& thing : things)
            {
                std::visit([&parameters](const auto& cmp)
                           {
                               cmp.test(parameters);
                           }, thing);
            }

            return false;
        }
    };
}

