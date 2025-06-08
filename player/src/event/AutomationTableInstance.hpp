#pragma once
#include <unordered_map>

#include "automation/AutomationInstance.hpp"
#include "automation/PropertyProvider.hpp"

namespace automation
{
    class AutomationTableInstance : public AutomationInstance
    {
    public:
        AutomationTableInstance();
        PropertyInstanceContainer getContainer(PropertyProviderPtr provider) override;
        ~AutomationTableInstance() override = default;

    private:
        // Store all automated properties
        std::unordered_map<PropertyProviderPtr, PropertyInstanceContainer> containers;
    };
}
