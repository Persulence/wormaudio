#pragma once

#include "event/LogicTickInfo.hpp"

namespace sm
{
    class ParameterLookup;
}

namespace condition
{
    template <class T>
    struct ConditionBase
    {
        [[nodiscard]] player::Sample test(const sm::ParameterLookup& pl, const event::LogicTickInfo& info) const
        {
            return static_cast<const T*>(this)->testImpl(pl, info);
        }

    private:
        ConditionBase() = default;
        friend T;
    };
}
