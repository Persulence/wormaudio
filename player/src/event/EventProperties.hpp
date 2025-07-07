#pragma once

#include <algorithm>

#include "instance/spatial.hpp"

namespace event
{
    class EventProperties
    {
    public:
        float minDistance = 0;
        float maxDistance = 10;

        player::Attenuation attenuation{player::Attenuation::LINEAR};

        float attenuate(float distance) const
        {
            const float f = 1 - std::clamp((distance - minDistance) / (maxDistance - minDistance), 0.f, 1.f);

            return player::attenuate(attenuation, f);
        }

    };
}
