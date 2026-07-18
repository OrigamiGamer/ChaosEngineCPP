#pragma once

#include "chaos/chaos.h"


namespace chaos {


    template<typename T>
    struct vec2 {
        T x{};
        T y{};

        vec2() {}

        vec2(T x, T y) : x(x), y(y) {}


        vec2<T> operator+(const vec2<T>& other) const
        {
            return { this->x + other.x, this->y + other.y };
        }


        vec2<T> operator-(const vec2<T>& other) const
        {
            return { this->x - other.x, this->y - other.y };
        }


        vec2<T> operator*(const vec2<T>& other) const
        {
            return { this->x * other.x, this->y * other.y };
        }


        vec2<T> operator/(const vec2<T>& other) const
        {
            return { this->x / other.x, this->y / other.y };
        }


        void operator+=(const vec2<T>& other)
        {
            this->x += other.x; this->y += other.y;
        }


        void operator-=(const vec2<T>& other)
        {
            this->x -= other.x; this->y -= other.y;
        }


        void operator*=(const vec2<T>& other)
        {
            this->x *= other.x; this->y *= other.y;
        }


        void operator/=(const vec2<T>& other)
        {
            this->x /= other.x; this->y /= other.y;
        }


    };



    template<typename T>
    struct vec3 {
        T x;
        T y;
        T z;

        vec3() {}

        vec3(T x, T y, T z) : x(x), y(y), z(z) {}


        vec3<T> operator+(const vec3<T>& other) const
        {
            return { this->x + other.x, this->y + other.y, this->z + other.z };
        }


        vec3<T> operator-(const vec3<T>& other) const
        {
            return { this->x - other.x, this->y - other.y, this->z - other.z };
        }


        vec3<T> operator*(const vec3<T>& other) const
        {
            return { this->x * other.x, this->y * other.y, this->z * other.z };
        }


        vec3<T> operator/(const vec3<T>& other) const
        {
            return { this->x / other.x, this->y / other.y, this->z / other.z };
        }


        void operator+=(const vec3<T>& other)
        {
            this->x += other.x; this->y += other.y; this->z += other.z;
        }


        void operator-=(const vec3<T>& other)
        {
            this->x -= other.x; this->y -= other.y; this->z -= other.z;
        }


        void operator*=(const vec3<T>& other)
        {
            this->x *= other.x; this->y *= other.y; this->z *= other.z;
        }


        void operator/=(const vec3<T>& other)
        {
            this->x /= other.x; this->y /= other.y; this->z /= other.z;
        }


    };


}