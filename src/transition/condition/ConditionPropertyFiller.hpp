#pragma once

#include "property/PropertyFiller.hpp"
#include "state/ConditionList.hpp"

namespace ui
{
    /// Base class for condition property fillers. Impl contains std::variant visitor for conditions.
    class ConditionPropertyFiller : public PropertyFiller
    {
    public:
        static std::unique_ptr<PropertyFiller> create(condition::Condition& condition);
    };
}
