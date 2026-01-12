#pragma once
#include "math/Vec2.h"

namespace math {

    inline float clampf(float v, float lo, float hi) {
        return (v < lo) ? lo : (v > hi) ? hi : v;
    }

    inline float lerpf(float a, float b, float t) {
        return a + (b - a) * t;
    }

    inline float dist(const Vec2& a, const Vec2& b) {
        return (a - b).length();
    }

} // namespace math
