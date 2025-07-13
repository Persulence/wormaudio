// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "Automation.hpp"
#include "Property.hpp"

namespace automation
{
    Property createProperty(PropertyName id, AutomationValue defaultVal, Unit unit)
    {
        return std::make_unique<PropertyDef>(id, defaultVal, unit);
    }
}
