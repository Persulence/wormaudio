#pragma once

#include <vector>

#include "PropertyProvider.hpp"
#include "juce_core/system/juce_PlatformDefs.h"

namespace automation
{
    class PropertyInstanceHandle;

    struct PropertyInstanceContainer
    {
        std::vector<PropertyInstanceHandle> properties;
    };

    class AutomationInstance
    {
    public:
        AutomationInstance() = default;
        virtual PropertyInstanceContainer getContainer(PropertyProviderPtr provider) = 0;
        virtual ~AutomationInstance() = default;

        JUCE_DECLARE_NON_COPYABLE(AutomationInstance)
    };
}
