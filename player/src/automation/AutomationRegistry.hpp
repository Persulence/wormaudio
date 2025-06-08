#pragma once
#include <unordered_map>

#include "Automation.hpp"
#include "PropertyProvider.hpp"

namespace automation
{
    struct PropertyContainer
    {
        std::vector<Property> properties;
    };

    class AutomationRegistry
    {
    public:
        struct Identifier
        {
            std::shared_ptr<PropertyProvider> parent;
            PropertyName name;

            bool operator==(const Identifier& other) const
            {
                return name == other.name && parent == other.parent;
            }

            struct Hash
            {
                size_t operator()(const Identifier& id) const noexcept
                {
                    return std::hash<std::shared_ptr<PropertyProvider>>{}(id.parent)
                        ^ std::hash<PropertyName>{}(id.name);
                }
            };
        };

        virtual ~AutomationRegistry() = default;

        // Exposes the property for automation
        void reg(const std::shared_ptr<PropertyProvider> &provider);
        void removeAll(const PropertyProviderKey& provider);

        std::unordered_map<PropertyProviderKey, PropertyContainer> registry;

    protected:
    };
}
