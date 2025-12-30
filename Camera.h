#pragma once
#include "Utils.h"

class Camera {
public:
    Vec2 center{ 0,0 };
    float zoom = 1.0f;

    Vec2 worldToScreen(const Vec2& w, float W, float H) const;
    Vec2 screenToWorld(const Vec2& s, float W, float H) const;

    void pan(const Vec2& deltaWorld) { center = center + deltaWorld; }

    // zoom γύρω από το cursor (κρατάει το σημείο κάτω από το cursor σταθερό)
    void zoomAtScreen(const Vec2& screenPos, float newZoom, float W, float H);

};
