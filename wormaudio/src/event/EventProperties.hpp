// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "instance/spatial.hpp"
#include "util/serialization_util.hpp"

namespace event
{
    class EventProperties
    {
    public:
        float minDistance = 0;
        float maxDistance = 10;
        float falloff = 1;

        player::Attenuation attenuation{player::Attenuation::LINEAR};

        EventProperties() = default;

        float attenuate(float distance) const
        {
            float f = player::attenuate(attenuation, minDistance, maxDistance, falloff, distance);

            return std::isnan(f) ? 1 : f;
        }

    private:
        FRIEND_CEREAL
        // EventProperties() = default;

        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(
                make_nvp("minDistance", minDistance),
                make_nvp("maxDistance", maxDistance),
                make_nvp("rolloff", falloff),
                make_nvp("attenuation", attenuation));
        }
    };
}
