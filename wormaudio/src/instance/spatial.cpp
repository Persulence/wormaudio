// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "spatial.hpp"

#include <cmath>
#include <algorithm>

namespace player
{
    /// Yaw is treated as being 0 at +Z and 90 at +X
    float earDistance(instance::Vec3f soundPos, instance::Vec3f listenerPos, float yaw, float maxDistance)
    {
        using namespace instance;
        // Find the angle between listenerPos -> soundPos and the line normal to the listener's direction

        auto to = soundPos - listenerPos;
        auto c = std::cos(yaw);
        auto s = std::sin(yaw);

        auto facing = Vec3f{s, 0, c};
        constexpr auto up = Vec3f{0, 1, 0};

        auto perpendicular = facing.cross(up);

        // Scalar project onto the listener's 'ear axis'
        // Divide by max distance to get a value between -1 and 1 when within listening range
        // Clamp to be safe
        auto scalar = std::clamp(to.abs() * std::cos(perpendicular.angleTo(to)) / maxDistance, -1.0, 1.0);

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
