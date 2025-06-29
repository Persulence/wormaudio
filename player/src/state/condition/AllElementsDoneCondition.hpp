#pragma once
#include "Condition.hpp"

namespace condition
{
    class AllElementsDoneCondition : public ConditionBase<AllElementsDoneCondition>
    {
    public:
        AllElementsDoneCondition() = default;

        [[nodiscard]] player::Sample testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance& currentState) const;

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {

        }
    };
}
