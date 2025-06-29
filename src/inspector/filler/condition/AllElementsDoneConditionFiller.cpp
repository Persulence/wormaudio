#include "AllElementsDoneConditionFiller.hpp"

namespace ui
{
    AllElementsDoneConditionFiller::AllElementsDoneConditionFiller(
            condition::AllElementsDoneCondition &condition):
        condition(condition)
    {

    }

    void AllElementsDoneConditionFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("All Elements Done"));
    }
}
