#include "RandomConditionFiller.hpp"

#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    RandomConditionFiller::RandomConditionFiller(condition::RandomCondition &condition_):
        condition(condition_)
    {

    }

    void RandomConditionFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Random"));

        add(std::make_unique<DataEntryPropertyWidget<float>>("Chance", condition.chance, parse::parseFloat));
    }
}
