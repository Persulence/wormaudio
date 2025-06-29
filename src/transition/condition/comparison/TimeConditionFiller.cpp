#include "TimeConditionFiller.hpp"

#include "panel/ChoicePropertyWidget.hpp"
#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    using namespace condition;

    TimeConditionFiller::TimeConditionFiller(TimeCondition &condition_):
        condition(condition_)
    {
        setHeader(std::make_unique<SectionHeader>("Time delay"));
    }

    void TimeConditionFiller::initProperties()
    {
        auto time = std::make_unique<DataEntryPropertyWidget<player::Seconds>>("Time", condition.time.value, parse::parseSeconds);

        add(std::move(time));
        add(ChoicePropertyWidget<player::TimeType>::create("Reference", {
            {"Since entering state", player::TimeType::IN_STATE},
            {"Since event start", player::TimeType::SINCE_EVENT_START}
        }, &condition.time.type));
        add(ChoicePropertyWidget<TimeOperator>::create("Condition", {
            {"≤", TimeOperator::LESS_EQUAL},
            {"≥", TimeOperator::GREATER_EQUAL}
        }, &condition.op));

    }
}
