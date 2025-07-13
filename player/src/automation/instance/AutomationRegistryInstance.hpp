// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <vector>

#include "automation/AutomationRegistry.hpp"
#include "automation/PropertyProvider.hpp"
#include "util/class_util.h"

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
