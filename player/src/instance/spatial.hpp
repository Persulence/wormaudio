#pragma once

#include "instance.hpp"

namespace player
{
    float earDistance(instance::Vec3f soundPos, instance::Vec3f listenerPos, float yaw, float maxDistance);

    enum class Attenuation
    {
        LINEAR,
    };

    inline float attenuate(Attenuation attenuation, float f)
    {
        switch (attenuation)
        {
            case Attenuation::LINEAR:
            {
                return f;
            }
        }
        return f;
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
