// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "TimeConditionFiller.hpp"

#include "inspector/filler/TempoInspectorFiller.hpp"
#include "panel/ChoicePropertyWidget.hpp"
#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    using namespace condition;

    TimeConditionFiller::TimeConditionFiller(TimeCondition &condition_, int index):
        ConditionPropertyFiller(index),
        condition(condition_)
    {
        setHeader(std::make_unique<SectionHeader>("Time delay"));
    }

    void TimeConditionFiller::initProperties()
    {
        add(ChoicePropertyWidget<player::TimeType>::create("Reference", {
            {"Since entering state", player::TimeType::IN_STATE},
            {"Since event start", player::TimeType::SINCE_EVENT_START}
        }, &condition.time.type));
        add(ChoicePropertyWidget<TimeOperator>::create("Condition", {
            {"≤", TimeOperator::LESS_EQUAL},
            {"≥", TimeOperator::GREATER_EQUAL}
        }, &condition.op));

        add(std::make_unique<BoolDataPropertyWidget>("Use Tempo", condition.time.useTempo));

        // Refresh all children when this is changed
        condition.time.useTempo.setupListener(&useTempoListener, [this](auto& val)
        {
            onChanged(SOFT);
        });

        if (*condition.time.useTempo)
        {
            add(std::make_unique<TempoInspectorFiller>(condition.time.tempo));
            add(std::make_unique<DataEntryPropertyWidget<double>>("Time (beats)", timeBeats, parse::parseBeats));
            timeBeats = condition.time.tempo.secondsToBeats(*condition.time.valueSeconds);
            timeBeats.setValue(condition.time.tempo.secondsToBeats(*condition.time.valueSeconds));

            // Callback to update time (s)
            auto updateTime = [this](auto&) { condition.time.valueSeconds = condition.time.tempo.beatsToSeconds(timeBeats.getValue()); };

            timeBeatsListener.setCallback(updateTime);
            timeSigListener.setCallback(updateTime);

            // Listen for changes to BPM and time signature
            timeBeats.setupListener(&timeBeatsListener);
            condition.time.tempo.bpm.setupListener(&timeBeatsListener);
            condition.time.tempo.timeSig.setupListener(&timeSigListener);
        }

        add(std::make_unique<DataEntryPropertyWidget<player::Seconds>>("Time (s)", condition.time.valueSeconds, parse::parseSeconds));

    }
}
