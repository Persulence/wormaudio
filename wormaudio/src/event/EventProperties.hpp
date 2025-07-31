// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
