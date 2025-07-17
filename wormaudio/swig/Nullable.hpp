// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include <optional>

namespace binding
{
    /// For communication with the JVM
    /// This class has very explicit SWIG marshalling.
    /// Applying it to this and not std::optional makes it harder to accidentally apply invalid (and possibly memory leaky) marshalling.
    template<typename T>
    class Nullable
    {
        std::optional<T> backing;

    public:
        Nullable() = default;
        Nullable(T&& value): backing(value) {}

        explicit operator bool() const
        {
            return backing;
        }

        bool hasValue()
        {
            return static_cast<bool>(backing);
        }

        T& value() &
        {
            return *backing;
        }
    };
}
