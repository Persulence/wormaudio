#pragma once
#include "transition/condition/ConditionPropertyFiller.hpp"

namespace ui
{
    class TimeConditionFiller : public ConditionPropertyFiller
    {
    public:
        explicit TimeConditionFiller(condition::TimeCondition& condition_);

        void initProperties() override;

    private:
        condition::TimeCondition &condition;
    };
}
