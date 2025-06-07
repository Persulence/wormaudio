#pragma once
#include "Automation.hpp"

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
