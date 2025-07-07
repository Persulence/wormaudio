#include "spatial.hpp"

#include <cmath>
#include <iostream>
#include <tuple>
#include <tuple>
#include <tuple>
#include <tuple>

namespace player
{
    /// Yaw is treated as being 0 at +Z and 90 at +X
    float earDistance(instance::Vec3f soundPos, instance::Vec3f listenerPos, float yaw)
    {
        using namespace instance;
        // Find the angle between listenerPos -> soundPos and the line normal to the listener's direction

        auto to = soundPos - listenerPos;
        auto c = std::cos(yaw);
        auto s = std::sin(yaw);

        auto facing = Vec3f{s, 0, c};
        auto up = Vec3f{0, 1, 0};

        auto perpendicular = facing.cross(up);

        auto scalar = to.abs() * std::cos(perpendicular.angleTo(to));

        if (std::isnan(scalar))
            return 0;

        return scalar;
    }
}


// int main()
// {
//     using namespace instance;
//     using namespace player;
//
//     Vec3f v1{0, 0, 1}; // South
//     Vec3f v2{1, 0, 0}; // East
//     auto angle = v1.angleTo(v2); // +90°
//
//     auto soundPos = Vec3f{1, 0, 1};
//     auto listener = Vec3f{0, 0, 2};
//
//     earDistance(soundPos, listener, 3.141 / 1);
// }
