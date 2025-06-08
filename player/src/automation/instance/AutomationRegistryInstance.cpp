#include "AutomationRegistryInstance.hpp"

#include "automation/Property.hpp"

namespace automation
{
    PropertyInstanceContainer::PropertyInstanceContainer(PropertyContainer container)
    {
        for (auto& prop : container.properties)
        {
            instances.push_back(PropertyInstanceHandle{std::make_shared<PropertyInstance>(prop)});
        }
    }
}
