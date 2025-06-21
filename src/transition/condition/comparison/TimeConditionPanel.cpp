#include "TimeConditionPanel.hpp"

#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    TimeConditionPanel::TimeConditionPanel(condition::TimeCondition &condition_):
        condition(condition_)
    {
        TimeConditionPanel::initProperties();
    }

    void TimeConditionPanel::initProperties()
    {
        add(std::make_shared<ValuePropertyWidget>("data", condition.time.value.backing));
    }
}
