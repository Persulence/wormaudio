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

#pragma once
#include "transition/condition/ConditionPropertyFiller.hpp"

namespace ui
{
    class TimeConditionFiller : public ConditionPropertyFiller
    {
    public:
        TimeConditionFiller(condition::TimeCondition &condition_, int index);

        void initProperties() override;

    private:
        DISABLE_COPY(TimeConditionFiller)
        DISABLE_MOVE(TimeConditionFiller)

        condition::TimeCondition &condition;
        util::Data<bool>::Listener useTempoListener;
        util::Data<player::Beats> timeBeats;
        util::Data<player::Beats>::MultiListener timeBeatsListener;
        util::Data<player::TimeSignature>::MultiListener timeSigListener;
    };
}
