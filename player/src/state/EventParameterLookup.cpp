
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