#include "Automation.hpp"
#include "Property.hpp"

namespace automation
{
    Property createProperty(PropertyIdentifier id, AutomationValue defaultVal, Unit unit)
    {
        return std::make_unique<PropertyDef>(id, defaultVal, unit);
    }
}
