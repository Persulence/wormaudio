// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once
#include <unordered_map>

#include "../automation/instance/AutomationRegistryInstance.hpp"
#include "automation/AutomationTable.hpp"
#include "automation/PropertyProvider.hpp"

namespace player
{
    class TransportControl;
}

namespace sm
{
    class EventParameterLookup;
}

namespace automation
{
    class AutomationTableInstance : public AutomationRegistryInstance
    {
    public:
        explicit AutomationTableInstance(AutomationTable& automation);
        ~AutomationTableInstance() override = default;

        PropertyInstanceContainer getContainer(PropertyProviderKey provider) override;
        void logicTick(const sm::EventParameterLookup& parameters, const player::TransportControl& transport) const;

    private:
        // Store all automated properties
        std::unordered_map<Property, PropertyInstanceHandle> allInstances;
        std::unordered_map<PropertyProviderKey, PropertyInstanceContainer> containers;
        AutomationTable& table;
    };
}
