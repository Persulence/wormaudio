#pragma once

#include "transition/condition/ConditionPropertyFiller.hpp"

namespace condition
{
    class QuantiseCondition;
}

namespace ui
{
    class QuantiseConditionFiller : public ConditionPropertyFiller
    {
    public:
        explicit QuantiseConditionFiller(condition::QuantiseCondition& condition_);
        void initProperties() override;

    private:
        condition::QuantiseCondition &condition;
    };
}
