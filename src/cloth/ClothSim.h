#pragma once
#include <vector>
#include "cloth/ClothPoint.h"
#include "cloth/ClothStick.h"

class ClothSim
{
public:
    void init(int cols, int rows, float spacing);
    void update(float dt);
    void draw() const;

private:
    std::vector<ClothPoint> m_points;
    std::vector<ClothStick> m_sticks;
    int m_dragIdx = -1;
    bool m_dragWasPinned = false;
    void cutAt(float x, float y, float radius);

};

