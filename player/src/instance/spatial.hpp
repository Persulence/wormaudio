// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <algorithm>

#include "instance.hpp"

namespace player
{
    float earDistance(instance::Vec3f soundPos, instance::Vec3f listenerPos, float yaw, float maxDistance);

    enum class Attenuation
    {
        NONE,
        LINEAR,
        LINEAR_ROLLOFF,
        INVERSE_DISTANCE,
    };

    inline float attenuate(Attenuation attenuation, float minDistance, float maxDistance, float rolloff, float distance)
    {
        switch (attenuation)
        {
            case Attenuation::NONE:
            {
                return 1;
            }
            case Attenuation::LINEAR:
            {
                distance = std::clamp(distance, minDistance, maxDistance);
                return 1 - (distance - minDistance) / (maxDistance - minDistance);
            }
            case Attenuation::LINEAR_ROLLOFF:
            {
                // Clamp the result as it drops below 0 when rolloff > 1
                return 1 - std::clamp(rolloff * (distance - minDistance) / (maxDistance - minDistance), 0.f, 1.f);
            }
            case Attenuation::INVERSE_DISTANCE:
            {
                return distance <= minDistance ? 1 : minDistance / (minDistance + rolloff * (distance - minDistance));
            }
        }

        return 1;
    }

    // inline void testDot()
    // {
    //     instance::Vec3f v1{1, 0, 0};
    //     instance::Vec3f v2{0, 1, 0};
    //     assert(v1.dot(v2) == 0);
    // }
    //
    // inline void testCross()
    // {
    //     instance::Vec3f v1{1, 0, 0};
    //     instance::Vec3f v2{0, 1, 0};
    //     instance::Vec3f result{0, 0, 1};
    //
    //     assert(v1.cross(v2) == result);
    // }
    //
    // inline void testAbs()
    // {
    //     instance::Vec3f v1{1, 0, 0};
    //     instance::Vec3f v2{1, 1, 0};
    //
    //     assert(v1.abs() == 1);
    //     assert(v2.abs() == std::sqrt(2));
    // }
    //
    // inline void testAngleTo()
    // {
    //     instance::Vec3f v1{1, 0, 0};
    //     instance::Vec3f v2{0, 1, 0};
    //
    //     auto thing = v1.dot(v2);
    //     auto angle = v1.angleTo(v2);
    //     assert(angle == std::numbers::pi / 2);
    // }
}
