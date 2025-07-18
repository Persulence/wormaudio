// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "state/condition/AllElementsDoneCondition.hpp"
#include "transition/condition/ConditionPropertyFiller.hpp"

namespace ui
{
    class AllElementsDoneConditionFiller : public ConditionPropertyFiller
    {
    public:
        AllElementsDoneConditionFiller(condition::AllElementsDoneCondition &condition, int index);

        void initProperties() override;

    private:
        condition::AllElementsDoneCondition& condition;
    };
}
