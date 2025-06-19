#pragma once

namespace sm
{
    class ParameterLookup;
}

namespace condition
{
    template <class T>
    struct ConditionBase
    {
        [[nodiscard]] bool test(const sm::ParameterLookup& pl) const
        {
            return static_cast<const T*>(this)->testImpl(pl);
        }

    private:
        ConditionBase() = default;
        friend T;
    };
}
