#include "Camera.h"

Vec2 Camera::worldToScreen(const Vec2& w, float W, float H) const {
    return { (w.x - center.x) * zoom + W * 0.5f, (w.y - center.y) * zoom + H * 0.5f };
}
Vec2 Camera::screenToWorld(const Vec2& s, float W, float H) const {
    return { ((s.x - W * 0.5f) / zoom) + center.x, ((s.y - H * 0.5f) / zoom) + center.y };
}
void Camera::zoomAtScreen(const Vec2& screenPos, float newZoom, float W, float H)
{
    // world θέση κάτω από το cursor ΠΡΙΝ το zoom
    Vec2 before = screenToWorld(screenPos, W, H);

    zoom = newZoom;

    // world θέση κάτω από το cursor ΜΕΤΑ το zoom
    Vec2 after = screenToWorld(screenPos, W, H);

    // μετακίνησε το center ώστε το before == after
    center = center + (before - after);
}
