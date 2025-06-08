#pragma once
#include <unordered_map>

#include "Automation.hpp"
#include "PropertyProvider.hpp"

namespace automation
{

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
        void reg(const PropertyProviderPtr& provider);
        void removeAll(const PropertyProviderPtr& provider);

    protected:
        // std::unordered_map<Identifier, Property, Identifier::Hash> registry;
        std::unordered_multimap<PropertyProviderPtr, Property> registry;
    };
}
