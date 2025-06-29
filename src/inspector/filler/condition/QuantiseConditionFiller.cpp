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
                onChanged(SOFT);
            });
        });

        if (*condition.useTempo)
        {
            add(std::make_unique<TempoInspectorFiller>(condition.tempo));
            add(std::make_unique<DataEntryPropertyWidget<double>>("Interval (beats)", condition.intervalBeats, parse::parseSeconds));
            condition.intervalBeats.setupListener(&beatsListener, [this](auto& val)
            {
                condition.intervalSeconds = condition.tempo.beatsToSeconds(val);
            });
        }

        // Show seconds regardless
        add(std::make_unique<DataEntryPropertyWidget<player::Seconds>>("Interval (s)", condition.intervalSeconds, parse::parseSeconds));
    }
}
