#pragma once

#include "event/LogicTickInfo.hpp"

namespace sm
{
    class EventParameterLookup;
    class StateInstance;
}

namespace condition
{
    template <class T>
    struct ConditionBase
    {
        [[nodiscard]] player::Sample test(const sm::EventParameterLookup& pl, const event::LogicTickInfo& info, const sm::StateInstance& currentState) const
        {
            return static_cast<const T*>(this)->testImpl(pl, info, currentState);
        }

    private:
        ConditionBase() = default;
        friend T;
    };
}
