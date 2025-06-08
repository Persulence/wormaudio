#pragma once

#include <vector>

#include "automation/AutomationRegistry.hpp"
#include "automation/PropertyProvider.hpp"
#include "juce_core/system/juce_PlatformDefs.h"

namespace automation
{
    class PropertyInstanceHandle;

    struct PropertyInstanceContainer
    {
        std::vector<PropertyInstanceHandle> instances;

        explicit PropertyInstanceContainer(PropertyContainer container);
    };

    class AutomationRegistryInstance
    {
    public:
        AutomationRegistryInstance() = default;
        virtual PropertyInstanceContainer getContainer(PropertyProviderKey provider) = 0;
        virtual ~AutomationRegistryInstance() = default;

        JUCE_DECLARE_NON_COPYABLE(AutomationRegistryInstance)
    };
}
