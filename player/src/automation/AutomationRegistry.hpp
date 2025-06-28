#pragma once

#include <unordered_map>
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/memory.hpp"

#include "Automation.hpp"
#include "PropertyProvider.hpp"
#include "cereal_optional_nvp.h"

namespace automation
{
    struct PropertyContainer
    {
        std::vector<Property> properties;

        INTERNAL_SERIALIZE
        {
            ar(properties);
        }
    };

    class AutomationRegistry
    {
    public:
        // struct Identifier
        // {
        //     std::shared_ptr<PropertyProvider> parent;
        //     PropertyName name;
        //
        //     bool operator==(const Identifier& other) const
        //     {
        //         return name == other.name && parent == other.parent;
        //     }
        //
        //     struct Hash
        //     {
        //         size_t operator()(const Identifier& id) const noexcept
        //         {
        //             return std::hash<std::shared_ptr<PropertyProvider>>{}(id.parent)
        //                 ^ std::hash<PropertyName>{}(id.name);
        //         }
        //     };
        // };

        AutomationRegistry() = default;

        // Exposes the property for automation
        void reg(const std::shared_ptr<PropertyProvider> &provider);
        void removeAll(const PropertyProviderKey& provider);

        std::unordered_map<PropertyProviderKey, PropertyContainer> registry;

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            // cereal::make_optional_nvp(ar, "registry",  registry);
        }
    };
}
