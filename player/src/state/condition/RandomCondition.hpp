#pragma once
#include "Condition.hpp"

namespace condition
{
    class RandomCondition : public ConditionBase<RandomCondition>
    {
    public:
        util::Data<float> chance{1.f};

        RandomCondition() = default;

        [[nodiscard]] player::Sample testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance &currentState) const;

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("chance", chance));
        }
    };
}
