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
