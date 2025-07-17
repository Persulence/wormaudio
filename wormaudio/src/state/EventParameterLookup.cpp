
// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "EventParameterLookup.hpp"

namespace sm
{
    using namespace player;

    void EventParameterLookup::resetStateTimer(Sample sample)
    {
        lastStateEnter = sample;
    }

    Sample EventParameterLookup::getReference(TimeType type) const
    {
        if (type == IN_STATE)
        {
            return lastStateEnter;
        }
        else
        {
            return 0;
        }
    }
}