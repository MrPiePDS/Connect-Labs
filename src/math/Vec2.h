#pragma once
#include <cmath>

namespace math {

    struct Vec2 {
        float x = 0.0f;
        float y = 0.0f;

        Vec2() = default;
        Vec2(float _x, float _y) : x(_x), y(_y) {}

        Vec2 operator+(const Vec2& r) const { return { x + r.x, y + r.y }; }
        Vec2 operator-(const Vec2& r) const { return { x - r.x, y - r.y }; }
        Vec2 operator*(float s) const { return { x * s, y * s }; }

        Vec2& operator+=(const Vec2& r) { x += r.x; y += r.y; return *this; }
        Vec2& operator-=(const Vec2& r) { x -= r.x; y -= r.y; return *this; }

        float length() const { return std::sqrt(x * x + y * y); }
    };

    inline float dot(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }

} // namespace math
