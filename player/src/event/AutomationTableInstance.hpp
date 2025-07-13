// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
