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
            return player::attenuate(attenuation, minDistance, maxDistance, falloff, distance);
        }

    };
}
