// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
            // WHY DOES THIS COMPILE????
            // PropertyProvider has no serialize function
            // cereal::make_optional_nvp(ar, "registry",  registry);
            // ar(cereal::make_nvp("registry",  registry));
        }
    };
}
