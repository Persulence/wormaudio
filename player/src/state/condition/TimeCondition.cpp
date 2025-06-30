#include "TimeCondition.hpp"

#include "event/LogicTickInfo.hpp"
#include "state/GlobalParameterLookup.hpp"

namespace condition
{
    player::Sample TimeCondition::testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance& currentState) const
    {
        auto reference = pl.getReference(time.type);

        const player::Sample timePoint = reference + info.toSamples(*time.valueSeconds);
        if (op == TimeOperator::GREATER_EQUAL)
        {
            if (timePoint >= info.blockBeginSamples && timePoint < info.blockEndSamples)
            {
                return timePoint - info.blockBeginSamples;
            }
            else if (info.blockBeginSamples >= timePoint)
            {
                // If time.value is less than the length of a block, and the previous transition occurs with a non-zero
                // handoff offset, it will not be possible to perform the next transition until the next block.
                return 0;
            }
        }
        else if (op == TimeOperator::LESS_EQUAL)
        {
            if (info.blockBeginSamples <= timePoint)
            {
                return 0;
            }
            else if (timePoint >= info.blockBeginSamples && timePoint < info.blockEndSamples)
            {
                return timePoint - info.blockBeginSamples;
            }
        }

        return -1;
    }
}
