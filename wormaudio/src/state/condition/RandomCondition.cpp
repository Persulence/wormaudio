// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "RandomCondition.hpp"

#include "juce_core/juce_core.h"

namespace condition
{
    player::Sample RandomCondition::testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance& currentState) const
    {
        auto rand = juce::Random::getSystemRandom().nextFloat();
        return rand <= *chance ? 0 : player::NULL_SAMPLE;
    }
}
