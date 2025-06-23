#include "TimeConditionFiller.hpp"

#include "panel/ChoicePropertyWidget.hpp"
#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    TimeConditionFiller::TimeConditionFiller(condition::TimeCondition &condition_):
        condition(condition_)
    {
    }

    void TimeConditionFiller::initProperties()
    {
        add(std::make_shared<ValuePropertyWidget>("Offset", condition.time.value.backing));
        add(std::make_shared<ChoicePropertyWidget<player::TimeType>>("Type", std::vector<ChoicePropertyWidget<player::TimeType>::Entry>{
            {"In state", player::TimeType::IN_STATE},
            {"Since event start", player::TimeType::SINCE_EVENT_START}
        }, &condition.time.type));
    }
}
