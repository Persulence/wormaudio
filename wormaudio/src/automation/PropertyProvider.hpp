// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <vector>
#include "util/serialization_util.hpp"
#include "serialization/cereal_poly_archives.hpp"

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
