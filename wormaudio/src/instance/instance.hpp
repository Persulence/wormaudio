// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once
#include <cmath>

// Allow overriding the type in the build system
// Someone might want to use floats instead of doubles for more speed at less precision
#ifndef WORMAUDIO_COORDINATE_TYPE
#define WORMAUDIO_COORDINATE_TYPE double
#endif

namespace instance
{
    template<typename T>
    struct Vec3
    {
        WORMAUDIO_COORDINATE_TYPE x = 0;
        WORMAUDIO_COORDINATE_TYPE y = 0;
        WORMAUDIO_COORDINATE_TYPE z = 0;

        Vec3 operator+(const Vec3& o) const
        {
            return {x + o.x, y + o.y, z + o.z};
        }

        Vec3 operator-(const Vec3& o) const
        {
            return {x - o.x, y - o.y, z - o.z};
        }

        Vec3 operator*(const T& o) const
        {
            return {x * o, y * o, z * o};
        }

        Vec3& operator*=(const T& o)
        {
            x *= o;
            y *= o;
            z *= o;
            return *this;
        }

        Vec3 operator/(const T& o) const
        {
            return {x / o, y / o, z / o};
        }

        Vec3& operator/=(const T& o)
        {
            x /= o;
            y /= o;
            z /= o;
            return *this;
        }

        T dot(const Vec3& o) const
        {
            return x * o.x + y * o.y + z * o.z;
        }

        Vec3 cross(const Vec3& o) const
        {
            return {
                y * o.z - z * o.y,
                x * o.z - z * o.x,
                x * o.y - y * o.x
            };
        }

        T abs() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        T angleTo(const Vec3& o) const
        {
            return std::acos(dot(o) / (abs() * o.abs()));
        }

        /// Project this vector onto o
        Vec3 proj(const Vec3& o) const
        {
            return o * (dot(o) / o.dot(o));
        }

        bool operator==(const Vec3& o) const
        {
            return x == o.x && y == o.y && z == o.z;
        }
    };

    using Vec3f = Vec3<WORMAUDIO_COORDINATE_TYPE>;
}
