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
    class ParameterLookup;
}

namespace automation
{
    class AutomationTableInstance : public AutomationRegistryInstance
    {
    public:
        explicit AutomationTableInstance(AutomationTable& automation);
        ~AutomationTableInstance() override = default;

        PropertyInstanceContainer getContainer(PropertyProviderKey provider) override;
        void logicTick(const sm::ParameterLookup& parameters, const player::TransportControl& transport) const;

    private:
        // Store all automated properties
        std::unordered_map<Property, PropertyInstanceHandle> allInstances;
        std::unordered_map<PropertyProviderKey, PropertyInstanceContainer> containers;
        AutomationTable& table;
    };
}
