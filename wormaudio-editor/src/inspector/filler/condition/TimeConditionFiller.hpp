// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
