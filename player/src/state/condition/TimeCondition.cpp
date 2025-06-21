#include "TimeCondition.hpp"

#include "event/LogicTickInfo.hpp"
#include "state/ParameterLookup.hpp"

namespace condition
{
    player::Sample TimeCondition::testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info) const
    {
        auto reference = pl.getReference(time.type);

        player::Sample adjusted = reference + info.toSamples(*time.value);
        if (adjusted > info.blockBeginSamples && adjusted < info.blockEndSamples)
        {
            return adjusted - info.blockBeginSamples;
        }
        else
        {
            return -1;
        }
    }

    bool TimeCondition::thisBlock(const sm::ParameterLookup &pl, const event::LogicTickInfo &info) const
    {
        return *time.value > info.blockBegin && *time.value < info.blockEnd;
    }
}
