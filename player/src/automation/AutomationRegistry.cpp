#include "AutomationRegistry.hpp"

#include "Property.hpp"

namespace automation
{
    void AutomationRegistry::reg(const PropertyProviderPtr& provider)
    {
        for (auto& property : provider->getProperties())
        {
            // registry.insert({Identifier{provider, property->getId()}, property});
            registry.emplace(provider, property);
        }
    }

    void AutomationRegistry::removeAll(const PropertyProviderPtr& provider)
    {
        const auto it = registry.find(provider);
        registry.erase(it, registry.end());
    }
}
