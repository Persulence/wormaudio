// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "transition/condition/ConditionPropertyFiller.hpp"

namespace condition
{
    class QuantiseCondition;
}

namespace ui
{
    class QuantiseConditionFiller : public ConditionPropertyFiller
    {
    public:
        explicit QuantiseConditionFiller(condition::QuantiseCondition& condition_);
        void initProperties() override;

    private:
        condition::QuantiseCondition &condition;
        util::Data<bool>::Listener useTempoListener;
        util::Data<player::Beats>::MultiListener beatsListener;
        util::Data<player::TimeSignature>::MultiListener timeSigListener;
    };
}
