#pragma once
#include "Node.h"

class GameState;

class Connection {
public:
    int a, ap, b, bp;
    ResourceType type;
    float rate = 5.0f;

    Connection(int A, int AP, int B, int BP, ResourceType t)
        :a(A), ap(AP), b(B), bp(BP), type(t) {
    }

    void transfer(GameState& gs, float dt);
    void draw(GameState& gs) const;
};
