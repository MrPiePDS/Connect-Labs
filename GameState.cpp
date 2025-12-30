// GameState.cpp  (ΔΙΟΡΘΩΜΕΝΟ - compile με τη SGG που έχεις)

#include "GameState.h"
#include "NodeTypes.h"
#include <sgg/graphics.h>

#include <algorithm> // std::min, std::max
#include <cmath>     // std::abs

Node* GameState::getNode(int id) const
{
    for (auto* n : nodes) if (n->id == id) return n;
    return nullptr;
}

bool GameState::pickPort(const Vec2& w, int& outNodeId, int& outPortIdx) const
{
    for (int i = (int)nodes.size() - 1; i >= 0; --i)
    {
        Node* n = nodes[i];
        int pi = n->hitPort(w);
        if (pi != -1) { outNodeId = n->id; outPortIdx = pi; return true; }
    }
    return false;
}

bool GameState::pickNode(const Vec2& w, int& outNodeId) const
{
    for (int i = (int)nodes.size() - 1; i >= 0; --i)
    {
        Node* n = nodes[i];
        if (n->hitBody(w)) { outNodeId = n->id; return true; }
    }
    return false;
}

void GameState::tryCreateConnection(int fromN, int fromP, int toN, int toP)
{
    Node* A = getNode(fromN);
    Node* B = getNode(toN);
    if (!A || !B) return;

    if (fromP < 0 || fromP >= (int)A->ports.size()) return;
    if (toP < 0 || toP >= (int)B->ports.size()) return;

    const Port& outP = A->ports[fromP];
    const Port& inP = B->ports[toP];

    // output -> input, same resource type
    if (!outP.isOutput) return;
    if (inP.isOutput)   return;
    if (outP.type != inP.type) return;

    // avoid duplicate exact
    for (auto* c : conns)
    {
        if (c->a == fromN && c->ap == fromP && c->b == toN && c->bp == toP) return;
    }

    conns.push_back(new Connection(fromN, fromP, toN, toP, outP.type));
}

void GameState::init()
{
    nodes.push_back(new NetworkNode(nextId++, { -300, 0 }));
    nodes.push_back(new DownloaderNode(nextId++, { -50, 0 }));
    nodes.push_back(new UploaderNode(nextId++, { 150, 0 }));
    nodes.push_back(new CollectorNode(nextId++, { 350, 0 }));

    // Αν θες ΜΟΝΟ χειροκίνητα connections, ΣΒΗΣΕ αυτά:
    conns.push_back(new Connection(1, 0, 2, 0, ResourceType::Text));
    conns.push_back(new Connection(2, 1, 3, 0, ResourceType::Text));
    conns.push_back(new Connection(3, 1, 4, 0, ResourceType::Money));
}

void GameState::update(float dt)
{
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    Vec2 mouseScreen{ (float)ms.cur_pos_x, (float)ms.cur_pos_y };

     // -------- CAMERA MOVE (WASD) (SGG: getKeyState) --------
    {
        Vec2 move{ 0,0 };
        if (graphics::getKeyState(graphics::SCANCODE_W)) move.y -= 1.0f;
        if (graphics::getKeyState(graphics::SCANCODE_S)) move.y += 1.0f;
        if (graphics::getKeyState(graphics::SCANCODE_A)) move.x -= 1.0f;
        if (graphics::getKeyState(graphics::SCANCODE_D)) move.x += 1.0f;

        if (len2(move) > 0.0f)
        {
            float L = len(move);
            move = move * (1.0f / L);

            float speed = camSpeed / cam.zoom;  // “σωστό” feeling όταν κάνεις zoom in
            cam.pan(move * (speed * dt));
        }
    }

    // -------- ZOOM (10% step per press) --------
    {
        static bool prevQ = false;
        static bool prevE = false;

        const float STEP = 1.10f;
        const float ZMIN = 0.25f;
        const float ZMAX = 4.0f;

        bool qNow = graphics::getKeyState(graphics::SCANCODE_Q);
        bool eNow = graphics::getKeyState(graphics::SCANCODE_E);

        bool qPress = (qNow && !prevQ);
        bool ePress = (eNow && !prevE);

        if (ePress)
        {
            float newZoom = cam.zoom * STEP;
            if (newZoom > ZMAX) newZoom = ZMAX;
            cam.zoomAtScreen(Vec2{ (float)ms.cur_pos_x, (float)ms.cur_pos_y }, newZoom, winW, winH);
        }
        else if (qPress)
        {
            float newZoom = cam.zoom / STEP;
            if (newZoom < ZMIN) newZoom = ZMIN;
            cam.zoomAtScreen(Vec2{ (float)ms.cur_pos_x, (float)ms.cur_pos_y }, newZoom, winW, winH);
        }

        prevQ = qNow;
        prevE = eNow;
    }


    // -------- CAMERA PAN (Right Mouse Drag) --------
    {
        if (ms.button_right_pressed)
        {
            panning = true;
            panStartMouse = mouseScreen;
            panStartCenter = cam.center;
        }

        if (panning && ms.button_right_down)
        {
            Vec2 dScreen = mouseScreen - panStartMouse;
            Vec2 dWorld = dScreen * (1.0f / cam.zoom);
            cam.center = panStartCenter - dWorld;
        }

        if (ms.button_right_released)
        {
            panning = false;
        }
    }
    // Recompute world mouse AFTER camera moved/zoomed
    Vec2 worldMouse = cam.screenToWorld(mouseScreen, winW, winH);

    // -------- LEFT CLICK: start connect OR start dragging a node --------
    if (ms.button_left_pressed)
    {
        int nId = -1, pIdx = -1;

        // 1) output port -> start connecting
        if (pickPort(worldMouse, nId, pIdx))
        {
            Node* n = getNode(nId);
            if (n && n->ports[pIdx].isOutput)
            {
                connecting = true;
                connectFromNode = nId;
                connectFromPort = pIdx;
                connectType = n->ports[pIdx].type;
            }
        }
        else
        {
            // 2) body -> start dragging
            int bodyId = -1;
            if (pickNode(worldMouse, bodyId))
            {
                draggingNode = true;
                dragNodeId = bodyId;
                Node* n = getNode(bodyId);
                dragOffset = worldMouse - n->pos;
            }
        }
    }

    // -------- While dragging node --------
    if (draggingNode && ms.button_left_down)
    {
        Node* n = getNode(dragNodeId);
        if (n)
        {
            Vec2 newPos = worldMouse - dragOffset;
            n->pos = newPos; // anti-overlap θα μπει μετά
        }
    }

    // -------- On release: finish connection & stop dragging --------
    if (ms.button_left_released)
    {
        if (connecting)
        {
            int toN = -1, toP = -1;
            if (pickPort(worldMouse, toN, toP))
                tryCreateConnection(connectFromNode, connectFromPort, toN, toP);
        }

        connecting = false;
        connectFromNode = connectFromPort = -1;

        draggingNode = false;
        dragNodeId = -1;
    }

    // -------- Simulation --------
    for (auto* n : nodes) n->update(*this, dt);
    for (auto* c : conns) c->transfer(*this, dt);
}

void GameState::draw()
{
    using namespace graphics;

    // -------- Background --------
    Brush bg;
    bg.fill_opacity = 1.0f;
    bg.fill_color[0] = 0.05f;
    bg.fill_color[1] = 0.07f;
    bg.fill_color[2] = 0.10f;
    drawRect(winW * 0.5f, winH * 0.5f, winW, winH, bg);

    // ---------- WORLD GRID (moves with camera) ----------
    graphics::Brush grid;
    grid.fill_opacity = 0.0f;
    grid.outline_opacity = 0.15f;
    grid.outline_width = 1.0f;
    grid.outline_color[0] = 0.7f;
    grid.outline_color[1] = 0.7f;
    grid.outline_color[2] = 0.7f;

    // πόσο απέχουν οι γραμμές στον ΚΟΣΜΟ (όχι στο screen)
    const float spacing = 50.0f;

    // τι world περιοχή φαίνεται τώρα στην οθόνη
    Vec2 wTL = cam.screenToWorld(Vec2{ 0.0f, 0.0f }, winW, winH);
    Vec2 wBR = cam.screenToWorld(Vec2{ winW, winH }, winW, winH);

    // βρες το πρώτο “πολλαπλάσιο του spacing” που πέφτει μέσα στο view
    float x0 = std::floor(wTL.x / spacing) * spacing;
    float y0 = std::floor(wTL.y / spacing) * spacing;

    // κάθε vertical γραμμή: world->screen και draw
    for (float wx = x0; wx <= wBR.x; wx += spacing)
    {
        Vec2 sA = cam.worldToScreen(Vec2{ wx, wTL.y }, winW, winH);
        Vec2 sB = cam.worldToScreen(Vec2{ wx, wBR.y }, winW, winH);
        graphics::drawLine(sA.x, sA.y, sB.x, sB.y, grid);
    }

    // κάθε horizontal γραμμή
    for (float wy = y0; wy <= wBR.y; wy += spacing)
    {
        Vec2 sA = cam.worldToScreen(Vec2{ wTL.x, wy }, winW, winH);
        Vec2 sB = cam.worldToScreen(Vec2{ wBR.x, wy }, winW, winH);
        graphics::drawLine(sA.x, sA.y, sB.x, sB.y, grid);
    }


    // -------- Connections (behind nodes) --------
    for (auto* c : conns) c->draw(*this);

    // -------- Nodes --------
    for (auto* n : nodes) n->draw(*this);

    // -------- Preview wire while connecting --------
    if (connecting)
    {
        Node* n = getNode(connectFromNode);
        if (n)
        {
            Vec2 w0 = n->portWorldPos(connectFromPort);
            Vec2 s0 = cam.worldToScreen(w0, winW, winH);

            MouseState ms;
            getMouseState(ms);

            Vec2 s1{ (float)ms.cur_pos_x, (float)ms.cur_pos_y };

            Brush br;
            br.fill_opacity = 0.0f;
            br.outline_opacity = 0.85f;
            br.outline_width = 2.0f;

            if (connectType == ResourceType::Text)
            {
                br.outline_color[0] = 0.20f;
                br.outline_color[1] = 1.00f;
                br.outline_color[2] = 0.70f;
            }
            else
            {
                br.outline_color[0] = 1.00f;
                br.outline_color[1] = 0.70f;
                br.outline_color[2] = 0.20f;
            }

            drawLine(s0.x, s0.y, s1.x, s1.y, br);
        }
    }

    // -------- HUD (Money) --------
    Brush t;
    t.fill_color[0] = 1.0f;
    t.fill_color[1] = 1.0f;
    t.fill_color[2] = 1.0f;

    char buf[64];
    sprintf_s(buf, "Money: %.1f", bankMoney);
    drawText(20.0f, 40.0f, 22.0f, buf, t);

    // ---- DEBUG: show where the code thinks the mouse is (world->screen) ----
    {
        graphics::MouseState ms;
        graphics::getMouseState(ms);

        Vec2 mouseScreen{ (float)ms.cur_pos_x, (float)ms.cur_pos_y };

        // convert screen -> world -> screen
        Vec2 w = cam.screenToWorld(mouseScreen, winW, winH);
        Vec2 s = cam.worldToScreen(w, winW, winH);

        graphics::Brush b;
        b.fill_opacity = 1.0f;
        b.fill_color[0] = 1.0f;
        b.fill_color[1] = 0.0f;
        b.fill_color[2] = 0.0f;

        graphics::drawDisk(s.x, s.y, 6.0f, b); // κόκκινη κουκίδα
    }

}

