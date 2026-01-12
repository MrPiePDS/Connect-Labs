#pragma once
#include <vector>
#include "cloth/ClothPoint.h"
#include "cloth/ClothStick.h"

class ClothBuilder {
public:
    static void buildGrid(
        int cols, int rows, float spacing,
        std::vector<ClothPoint>& points,
        std::vector<ClothStick>& sticks
    );
};
