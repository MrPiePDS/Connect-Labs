#pragma once
#include <cmath>

struct Vec2 {
    float x = 0, y = 0;
    Vec2() = default;
    Vec2(float xx, float yy) :x(xx), y(yy) {}
    Vec2 operator+(const Vec2& r) const { return { x + r.x,y + r.y }; }
    Vec2 operator-(const Vec2& r) const { return { x - r.x,y - r.y }; }
    Vec2 operator*(float s) const { return { x * s,y * s }; }
};

inline float dot(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }
inline float len2(const Vec2& v) { return dot(v, v); }
inline float len(const Vec2& v) { return std::sqrt(len2(v)); }
inline float clampf(float v, float a, float b) { return v < a ? a : (v > b ? b : v); }
