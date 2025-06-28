#pragma once

#include <vector>

#include "util/serialization_util.hpp"
#include "Automation.hpp"

namespace automation
{
    class PropertyProvider
    {
    public:
        [[nodiscard]] virtual std::vector<Property> getProperties() = 0;
        virtual ~PropertyProvider() = default;

        // INTERNAL_SERIALIZE
        // {
        // }
    };

    using PropertyProviderKey = std::shared_ptr<PropertyProvider>;
}
