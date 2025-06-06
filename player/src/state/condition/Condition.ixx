module;

export module sm:Condition;

import :ParameterLookup;

namespace condition
{
    export template <class T>
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
