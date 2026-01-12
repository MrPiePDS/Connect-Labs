#include "cloth/ClothBuilder.h"
#include "math/MathUtil.h"

void ClothBuilder::buildGrid(
    int cols, int rows, float spacing,
    std::vector<ClothPoint>& points,
    std::vector<ClothStick>& sticks
) {
    points.clear();
    sticks.clear();

    // points
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            bool pin = (y == 0); // pin top row
            points.emplace_back(
                math::Vec2(100 + x * spacing, 100 + y * spacing),
                pin
            );
        }
    }

    // sticks (horizontal + vertical)
    auto idx = [cols](int x, int y) { return y * cols + x; };

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (x < cols - 1)
                sticks.emplace_back(idx(x, y), idx(x + 1, y), spacing);
            if (y < rows - 1)
                sticks.emplace_back(idx(x, y), idx(x, y + 1), spacing);
        }
    }
}
