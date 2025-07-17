// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
        float x = 0;
        float y = 0;
        float z = 0;

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
