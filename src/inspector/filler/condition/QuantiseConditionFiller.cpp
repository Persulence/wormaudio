#include "QuantiseConditionFiller.hpp"

#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    QuantiseConditionFiller::QuantiseConditionFiller(condition::QuantiseCondition &condition_):
        condition(condition_)
    {
        setHeader(std::make_unique<SectionHeader>("Quantise"));
    }

    void QuantiseConditionFiller::initProperties()
    {
        add(std::make_unique<DataEntryPropertyWidget<player::Seconds>>("Interval", condition.interval, parse::parseSeconds));

        add(std::make_unique<TempoInspectorFiller>(condition.tempo));
    }
}
