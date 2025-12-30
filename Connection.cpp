#include "Connection.h"
#include "GameState.h"
#include <sgg/graphics.h>

void Connection::transfer(GameState& gs, float dt) {
    auto* A = gs.getNode(a);
    auto* B = gs.getNode(b);
    if (!A || !B) return;

    float amt = rate * dt;
    if (type == ResourceType::Text) {
        amt = std::min(A->text, amt);
        A->text -= amt; B->text += amt;
    }
    else {
        amt = std::min(A->money, amt);
        A->money -= amt; B->money += amt;
    }
}

void Connection::draw(GameState& gs) const {
    using namespace graphics;
    auto* A = gs.getNode(a);
    auto* B = gs.getNode(b);
    if (!A || !B) return;

    Vec2 sa = gs.cam.worldToScreen(A->portWorldPos(ap), gs.winW, gs.winH);
    Vec2 sb = gs.cam.worldToScreen(B->portWorldPos(bp), gs.winW, gs.winH);

    Brush br;
    br.outline_width = 3;
    br.outline_color[0] = 0; br.outline_color[1] = 1; br.outline_color[2] = 0.7f;
    drawLine(sa.x, sa.y, sb.x, sb.y, br);
}
