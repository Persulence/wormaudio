#pragma once

#include "property/PropertyFiller.hpp"
#include "state/condition/RandomCondition.hpp"

namespace ui
{
    class RandomConditionFiller : public PropertyFiller
    {
    public:
        explicit RandomConditionFiller(condition::RandomCondition& condition_);

        void initProperties() override;

    private:
        condition::RandomCondition& condition;
    };
}
