#pragma once
#include <vector>
#include "cloth/ClothPoint.h"

namespace cloth
{
    inline void applyGravity(std::vector<ClothPoint>& pts, float gY, float dt)
    {
        for (auto& p : pts)
            if (!p.pinned) p.pos.y += gY * dt * dt; // verlet-style accel
    }
}
