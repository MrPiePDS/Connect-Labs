#pragma once

struct ClothStick {
    int a = 0;             // index of point A
    int b = 0;             // index of point B
    float rest = 0.0f;     // rest length

    ClothStick() = default;
    ClothStick(int _a, int _b, float _r) : a(_a), b(_b), rest(_r) {}
};
