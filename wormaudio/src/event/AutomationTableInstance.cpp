// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "AutomationTableInstance.hpp"

#include "automation/Property.hpp"
#include "state/EventParameterLookup.hpp"

namespace automation
{
    AutomationTableInstance::AutomationTableInstance(AutomationTable &automation):
        table(automation)
    {
        for (auto& [key, container] : automation.registry)
        {
            auto instanceContainer = containers.emplace(key, PropertyInstanceContainer{container});

            for (auto& instanceHandle : instanceContainer.first->second.instances)
            {
                allInstances.emplace(instanceHandle->def, instanceHandle);
            }
        }

        // for (auto& thing : automation.getLinks())
        // {
        //     // containers.emplace()
        // }
    }

    PropertyInstanceContainer AutomationTableInstance::getContainer(const PropertyProviderKey provider)
    {
        PropertyInstanceContainer& result = containers.at(provider);
        return result;
    }

    void AutomationTableInstance::logicTick(const sm::EventParameterLookup &parameters, const player::TransportControl &transport) const
    {
        for (const auto& [parameter, property, mapping] : table.getLinks())
        {
            const auto value = parameters.getValue(parameter->getName());
            const auto transformed = mapping(value);
            allInstances.at(property)->setValue(transformed);
        }
    }
}
