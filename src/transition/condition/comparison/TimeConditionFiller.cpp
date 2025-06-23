#include "TimeConditionFiller.hpp"

#include "panel/ChoicePropertyWidget.hpp"
#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    using namespace condition;

    TimeConditionFiller::TimeConditionFiller(TimeCondition &condition_):
        condition(condition_)
    {
        setHeader(std::make_unique<SectionHeader>("Time condition"));
    }

    void TimeConditionFiller::initProperties()
    {
        add(std::make_shared<ValuePropertyWidget>("Time", condition.time.value.backing));
        // add(std::make_shared<ChoicePropertyWidget<player::TimeType>>("Time reference", std::vector<ChoicePropertyWidget<player::TimeType>::Entry>{
        //     {"In state", player::TimeType::IN_STATE},
        //     {"Since event start", player::TimeType::SINCE_EVENT_START}
        // }, &condition.time.type));
        add(ChoicePropertyWidget<player::TimeType>::create("Time", {
            {"In state", player::TimeType::IN_STATE},
            {"Since event start", player::TimeType::SINCE_EVENT_START}
        }, &condition.time.type));
        add(ChoicePropertyWidget<TimeOperator>::create("Condition", {
            {"≤", TimeOperator::LESS_EQUAL},
            {"≥", TimeOperator::GREATER_EQUAL}
        }, &condition.op));

    }
}
