#include "ConditionList.hpp"

namespace condition
{

    Condition & ConditionList::insertCondition(Condition condition)
    {
        conditions.push_back(std::move(condition));

        // Hmmmm
        return *(conditions.end() - 1);
    }

    player::Sample ConditionList::test(const sm::ParameterLookup &parameters, const event::LogicTickInfo &info) const
    {
        player::Sample result = -1;
        for (const auto& condition : conditions)
        {
            auto sample = std::visit([&parameters, &info](const auto& cmp)
            {
                return cmp.test(parameters, info);
            }, condition);

            result = std::max(result, sample);
        }

        return result;
    }
}
