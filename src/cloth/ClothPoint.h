#pragma once
#include "math/Vec2.h"

struct ClothPoint {
    math::Vec2 pos;
    math::Vec2 prev;
    bool pinned = false;

    ClothPoint() = default;
    ClothPoint(const math::Vec2& p, bool pin = false) : pos(p), prev(p), pinned(pin) {}
};
