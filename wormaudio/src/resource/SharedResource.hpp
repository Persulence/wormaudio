// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <memory>
#include <vector>

#include "util/serialization_util.hpp"
#include "cereal_optional_nvp.h"
#include "serialization/juce_uuid.hpp"

namespace resource
{
    class SharedResource;

    template <class T>
    concept IsResource = std::convertible_to<T&, SharedResource&>;

    using ResourceHandle = std::shared_ptr<SharedResource>;

    template<IsResource T>
    using Handle = std::shared_ptr<T>;

    /// Creates a
    template<IsResource T, typename... Args>
    Handle<T> make(Args&&... args)
    {
        // Pointer implementation can be changed without affecting other code
        return std::make_shared<T, Args...>(std::forward<Args>(args)...);
    }
    // using makeResource = std::make_shared<T, Args...>;

    class SharedResource
    {
    public:
        virtual ~SharedResource() = default;

        virtual std::vector<ResourceHandle> getChildResources()
        {
            return {};
        }
    };

    // UUID implementation will be changed when JUCE is removed.
    using UUID = juce::Uuid;

    class Identifiable
    {
    public:
        Identifiable(): uuid(UUID{}) {}

        virtual ~Identifiable() = default;

        UUID getUUID() { return uuid; };

    private:
        UUID uuid;

        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            cereal::make_optional_nvp(ar, "uuid", uuid);
        }
    };
}
