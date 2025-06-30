#pragma once

namespace instance
{
    struct Position
    {
        float listenerDistance{std::numeric_limits<float>::max()};
    };

    struct Velocity
    {
        float x{}, y{}, z{};
    };
}