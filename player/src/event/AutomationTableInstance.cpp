#include "AutomationTableInstance.hpp"

namespace automation
{
    AutomationTableInstance::AutomationTableInstance(const AutomationTable &automation)
    {
        for (auto& [key, container] : automation.registry)
        {
            containers.emplace(key, PropertyInstanceContainer{container});
        }
        // for (auto& thing : automation.getLinks())
        // {
        //     // containers.emplace()
        // }
    }

    PropertyInstanceContainer AutomationTableInstance::getContainer(const PropertyProviderKey provider)
    {
        return containers.at(provider);
    }
}
