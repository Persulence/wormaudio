#pragma once
#include <unordered_map>

#include "../automation/instance/AutomationRegistryInstance.hpp"
#include "automation/AutomationTable.hpp"
#include "automation/PropertyProvider.hpp"

namespace automation
{
    class AutomationTableInstance : public AutomationRegistryInstance
    {
    public:
        explicit AutomationTableInstance(const AutomationTable& automation);

        PropertyInstanceContainer getContainer(PropertyProviderKey provider) override;
        ~AutomationTableInstance() override = default;

    private:
        // Store all automated properties
        std::unordered_map<PropertyProviderKey, PropertyInstanceContainer> containers;
    };
}
