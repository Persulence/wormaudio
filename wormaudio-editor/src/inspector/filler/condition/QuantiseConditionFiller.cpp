// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "QuantiseConditionFiller.hpp"

#include "panel/MyPropertyPanel.hpp"
#include "inspector/filler/TempoInspectorFiller.hpp"

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
