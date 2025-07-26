// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
