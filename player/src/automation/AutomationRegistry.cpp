#include "AutomationRegistry.hpp"

#include "Property.hpp"

void automation::AutomationRegistry::reg(Property property)
{
    registry.emplace(property->getId(), property);
}
