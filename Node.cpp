#include "Node.h"
#include "GameState.h"
#include <sgg/graphics.h>

Vec2 Node::portWorldPos(int i) const {
    return pos + ports[i].localPos;
}

bool Node::hitBody(const Vec2& pt) const {
    return (pt.x > pos.x - w * 0.5f && pt.x < pos.x + w * 0.5f &&
        pt.y > pos.y - h * 0.5f && pt.y < pos.y + h * 0.5f);
}

int Node::hitPort(const Vec2& w) const {
    for (int i = 0; i < (int)ports.size(); ++i)
        if (len2(w - portWorldPos(i)) < 100) return i;
    return -1;
}

void Node::draw(GameState& gs) const {
    using namespace graphics;
    Brush b;
    b.fill_color[0] = 0.1f; b.fill_color[1] = 0.12f; b.fill_color[2] = 0.18f;
    b.outline_color[0] = 0.3f; b.outline_color[1] = 0.7f; b.outline_color[2] = 1.0f;
    b.outline_width = 2;

    Vec2 s = gs.cam.worldToScreen(pos, gs.winW, gs.winH);
    drawRect(s.x, s.y, w * gs.cam.zoom, h * gs.cam.zoom, b);

    for (int i = 0; i < (int)ports.size(); ++i)
    {
        const Port& p = ports[i];

        // 1) world θέση port = node.pos + localPos
        Vec2 wp = pos + p.localPos;

        // 2) screen θέση port (με camera)
        Vec2 sp = gs.cam.worldToScreen(wp, gs.winW, gs.winH);

        graphics::Brush pr;
        pr.fill_opacity = 1.0f;
        pr.outline_opacity = 1.0f;
        pr.outline_width = 2.0f;
        pr.outline_color[0] = 0.0f; pr.outline_color[1] = 0.0f; pr.outline_color[2] = 0.0f;

        if (p.type == ResourceType::Text) {
            pr.fill_color[0] = 0.2f; pr.fill_color[1] = 1.0f; pr.fill_color[2] = 0.7f;
        }
        else {
            pr.fill_color[0] = 1.0f; pr.fill_color[1] = 0.7f; pr.fill_color[2] = 0.2f;
        }

        // ζωγραφίζουμε το port πάνω στο node
        graphics::drawDisk(sp.x, sp.y, 7.0f * gs.cam.zoom, pr);
    }

    Brush t; t.fill_color[0] = 1; t.fill_color[1] = 1; t.fill_color[2] = 1;
    drawText(s.x - w / 2 + 10, s.y - h / 2 + 20, 16, title, t);
}
