#pragma once

namespace basic_type {
	template<typename T = float>
	struct vec2 {
		T x, y;
		bool operator==(vec2& a) const { return x == a.x && y == a.y; }
		bool operator!=(vec2& a) const { return !(*this == a); }
		vec2 operator+(vec2& a) const { return vec2{ x + a.x,y + a.y }; }
		vec2 operator-(vec2& a) const { return vec2{ x - a.x,y - a.y }; }
		vec2 operator*(vec2& a) const { return vec2{ x * a.x,y * a.y }; }
		vec2 operator/(vec2& a) const { return vec2{ x / a.x,y / a.y }; }
		vec2 operator+=(vec2& a) { x += a.x; y += a.y; return *this; }
		vec2 operator-=(vec2& a) { x -= a.x; y -= a.y; return *this; }
		vec2 operator*=(vec2& a) { x *= a.x; y *= a.y; return *this; }
		vec2 operator/=(vec2& a) { x /= a.x; y /= a.y; return *this; }
	};
	template<typename T = float>
	struct vec3 {
		T x, y, z;
		bool operator==(vec3& a) const { return x == a.x && y == a.y && z == a.z; }
		bool operator!=(vec3& a) const { return !(*this == a); }
		vec3 operator+(vec3& a) const { return vec3{ x + a.x,y + a.y,z + a.z }; }
		vec3 operator-(vec3& a) const { return vec3{ x - a.x,y - a.y ,z - a.z }; }
		vec3 operator*(vec3& a) const { return vec3{ x * a.x,y * a.y,z * a.z }; }
		vec3 operator/(vec3& a) const { return vec3{ x / a.x,y / a.y,z / a.z }; }
		vec3 operator+=(vec3& a) { x += a.x; y += a.y; z += a.z; return *this; }
		vec3 operator-=(vec3& a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
		vec3 operator*=(vec3& a) { x *= a.x; y *= a.y; z *= a.z; return *this; }
		vec3 operator/=(vec3& a) { x /= a.x; y /= a.y; z /= a.z; return *this; }
	};
}