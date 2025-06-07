#pragma once
#include "automation.hpp"

namespace automation
{
    class MappingFunction
    {
        AutomationValue operator()(const AutomationValue value) const
        {
            return value;
        }
    };
}
