#include "TimeCondition.hpp"

#include "state/ParameterLookup.hpp"

namespace condition
{
    bool TimeCondition::testImpl(const sm::ParameterLookup &pl) const
    {
        auto seconds = pl.getTime(time.type);



        return true;
    }
}
