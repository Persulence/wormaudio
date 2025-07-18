// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "AllElementsDoneConditionFiller.hpp"

namespace ui
{
    AllElementsDoneConditionFiller::AllElementsDoneConditionFiller(condition::AllElementsDoneCondition &condition, int index):
        ConditionPropertyFiller(index),
        condition(condition) {}

    void AllElementsDoneConditionFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("All Elements Done"));
    }
}
