#pragma once

#include "property/PropertyFiller.hpp"
#include "state/ConditionList.hpp"

namespace ui
{
    class ConditionPanel : public PropertyFiller
    {
    public:
        static std::unique_ptr<Component> create(condition::Condition& condition);

        explicit ConditionPanel();
    };
}
