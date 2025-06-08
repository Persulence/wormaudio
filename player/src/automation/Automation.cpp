#include "Automation.hpp"
#include "Property.hpp"

namespace automation
{
    Property createProperty(PropertyName id, AutomationValue defaultVal, Unit unit)
    {
        return std::make_unique<PropertyDef>(id, defaultVal, unit);
    }
}
