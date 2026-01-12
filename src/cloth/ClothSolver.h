#pragma once
#include <vector>
#include "cloth/ClothPoint.h"
#include "cloth/ClothStick.h"

class ClothSolver {
public:
    static void verlet(std::vector<ClothPoint>& pts, float dt, float gravityY);
    static void satisfy(std::vector<ClothPoint>& pts, const std::vector<ClothStick>& sticks, int iterations);
};
