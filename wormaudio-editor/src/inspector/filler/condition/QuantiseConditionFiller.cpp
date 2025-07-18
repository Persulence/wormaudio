// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "QuantiseConditionFiller.hpp"

#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    QuantiseConditionFiller::QuantiseConditionFiller(condition::QuantiseCondition &condition_, int index):
        ConditionPropertyFiller(index),
        condition(condition_) {}

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
            add(std::make_unique<DataEntryPropertyWidget<double>>("Interval (beats)", condition.intervalBeats, parse::parseBeats));

            condition.intervalBeats = condition.tempo.secondsToBeats(*condition.intervalSeconds);
            auto updateTime = [this](auto&) { condition.intervalSeconds = condition.tempo.beatsToSeconds(*condition.intervalBeats); };

            beatsListener.setCallback(updateTime);
            timeSigListener.setCallback(updateTime);

            condition.intervalBeats.setupListener(&beatsListener);
            condition.tempo.bpm.setupListener(&beatsListener);
            condition.tempo.timeSig.setupListener(&timeSigListener);
        }

        // Show seconds regardless
        add(std::make_unique<DataEntryPropertyWidget<player::Seconds>>("Interval (s)", condition.intervalSeconds, parse::parseSeconds));
    }
}
