#pragma once

#include <vector>

#include "Automation.hpp"

namespace automation
{
    class PropertyProvider
    {
    public:
        [[nodiscard]] virtual std::vector<Property> getProperties() = 0;
        virtual ~PropertyProvider() = default;
    };

    using PropertyProviderPtr = std::shared_ptr<PropertyProvider>;
}
