#pragma once

#include "instance/spatial.hpp"

namespace event
{
    class EventProperties
    {
    public:
        float minDistance = 0;
        float maxDistance = 10;
        float falloff = 1;

        player::Attenuation attenuation{player::Attenuation::LINEAR};

        float attenuate(float distance) const
        {
            float f = player::attenuate(attenuation, minDistance, maxDistance, falloff, distance);

            return std::isnan(f) ? 1 : f;
        }

    };
}
