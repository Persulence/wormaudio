#pragma once
#include "property/PropertyFiller.hpp"
#include "state/condition/AllElementsDoneCondition.hpp"

namespace ui
{

    class AllElementsDoneConditionFiller : public PropertyFiller
    {
    public:
        explicit AllElementsDoneConditionFiller(condition::AllElementsDoneCondition& condition);

        void initProperties() override;

    private:
        condition::AllElementsDoneCondition& condition;
    };
}
