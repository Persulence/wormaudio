// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
