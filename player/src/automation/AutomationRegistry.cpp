// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "AutomationRegistry.hpp"

#include "Property.hpp"

namespace automation
{
    void AutomationRegistry::reg(const std::shared_ptr<PropertyProvider> &provider)
    {
        registry[provider];
        for (auto& property : provider->getProperties())
        {
            // registry.insert({Identifier{provider, property->getId()}, property});
            // registry.emplace(provider, property);
            registry[provider].properties.push_back(property);
        }
    }

    void AutomationRegistry::removeAll(const PropertyProviderKey& provider)
    {
        const auto it = registry.find(provider);
        registry.erase(it, registry.end());
    }
}
