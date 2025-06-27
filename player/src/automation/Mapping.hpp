#pragma once
#include "Automation.hpp"
#include "cereal/access.hpp"
#include "util/serialization_util.hpp"

namespace automation
{
    class MappingFunction
    {
    public:
        MappingFunction() = default;

        AutomationValue operator()(const AutomationValue value) const
        {
            // TODO
            return value;
        }

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
        }
    };
}
