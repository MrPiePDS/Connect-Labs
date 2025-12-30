#pragma once
#include "Camera.h"
#include "Connection.h"
#include <vector>

class GameState {
public:
    float winW = 1280, winH = 720;
    Camera cam;
    float bankMoney = 0;

    std::vector<Node*> nodes;
    std::vector<Connection*> conns;
    int nextId = 1;

    // --- Interaction: dragging nodes
    bool draggingNode = false;
    int  dragNodeId = -1;
    Vec2 dragOffset{ 0,0 };

    // --- Interaction: connecting ports
    bool connecting = false;
    int  connectFromNode = -1;
    int  connectFromPort = -1;
    ResourceType connectType = ResourceType::Text;

    bool pickPort(const Vec2& w, int& outNodeId, int& outPortIdx) const;
    bool pickNode(const Vec2& w, int& outNodeId) const;
    void tryCreateConnection(int fromN, int fromP, int toN, int toP);

    // --- Camera controls ---
    float camSpeed = 600.0f;       // world units / sec (ρυθμίζεται)
    float zoomTarget = 1.0f;       // snap target
    bool  panning = false;
    Vec2  panStartMouse{ 0,0 };      // screen coords
    Vec2  panStartCenter{ 0,0 };     // world coords (camera center)
    bool prevQ = false;
    bool prevE = false;

    void init();
    void update(float dt);
    void draw();

    Node* getNode(int id) const;
};
