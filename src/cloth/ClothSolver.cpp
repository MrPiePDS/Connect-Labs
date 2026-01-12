#include "cloth/ClothSolver.h"
#include "math/MathUtil.h"
#include "cloth/ClothForces.h"


void ClothSolver::verlet(std::vector<ClothPoint>& pts, float dt, float gravityY)
{
    const float dt2 = dt * dt;

    for (auto& p : pts) {
        if (p.pinned) continue;

        math::Vec2 v = p.pos - p.prev;
        p.prev = p.pos;

        // integrate
        p.pos += v;
    }
    cloth::applyGravity(pts, gravityY, dt);
}

void ClothSolver::satisfy(std::vector<ClothPoint>& pts, const std::vector<ClothStick>& sticks, int iterations)
{
    for (int it = 0; it < iterations; ++it) {
        for (const auto& s : sticks) {
            auto& a = pts[s.a];
            auto& b = pts[s.b];

            math::Vec2 delta = b.pos - a.pos;
            float d = delta.length();
            if (d <= 0.0001f) continue;
            if (d <= s.rest) continue;   // rope: allow compression
            float diff = (d - s.rest) / d;
            math::Vec2 off = delta * (0.35f * diff);

            if (!a.pinned) a.pos += off;
            if (!b.pinned) b.pos -= off;
        }
    }
}
