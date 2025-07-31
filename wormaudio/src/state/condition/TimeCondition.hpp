// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "Condition.hpp"

#include "util/Time.hpp"
#include "util/Data.hpp"

namespace event
{
    struct LogicTickInfo;
}

namespace condition
{
    struct TimePos
    {
        util::Data<player::Seconds> valueSeconds;
        player::TimeType type{player::IN_STATE};

        player::Tempo tempo;
        util::Data<bool> useTempo;

        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(make_nvp("value", valueSeconds));
            ar(make_nvp("type", type));
            ar(make_nvp("useTempo", useTempo));
            ar(make_nvp("tempo", tempo));
        }
    };

    enum class TimeOperator
    {
        GREATER_EQUAL,
        LESS_EQUAL
    };

    class TimeCondition : public ConditionBase<TimeCondition>
    {
    public:
        TimePos time;
        TimeOperator op{TimeOperator::GREATER_EQUAL};

        TimeCondition() = default;

        [[nodiscard]] player::Sample testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance &currentState) const;

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            ar(time, op);
        }
    };
}
