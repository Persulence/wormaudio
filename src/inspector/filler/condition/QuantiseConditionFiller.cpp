#include "QuantiseConditionFiller.hpp"

#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    QuantiseConditionFiller::QuantiseConditionFiller(condition::QuantiseCondition &condition_):
        condition(condition_)
    {
    }

    void QuantiseConditionFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Quantise"));

        add(std::make_unique<BoolDataPropertyWidget>("Use Tempo", condition.useTempo));

        condition.useTempo.setupListener(&useTempoListener, [this](bool val)
        {
            juce::MessageManager::callAsync([this]
            {
                refresh();
            });
        });

        if (*condition.useTempo)
        {
            add(std::make_unique<TempoInspectorFiller>(condition.tempo));
            add(std::make_unique<DataEntryPropertyWidget<double>>("Interval (beats)", condition.intervalBeats, parse::parseSeconds));
        }
        else
        {
            add(std::make_unique<DataEntryPropertyWidget<player::Seconds>>("Interval (s)", condition.intervalSeconds, parse::parseSeconds));
        }
    }
}
