#pragma once
#include "Utils.h"
#include <string>
#include <vector>

enum class ResourceType { Text, Money };

struct Port {
    std::string name;
    ResourceType type;
    bool isOutput = false;
    Vec2 localPos;
};

class GameState;

class Node {
public:
    int id = -1;
    std::string title;
    Vec2 pos;
    float w = 190, h = 110;

    float text = 0, money = 0;
    std::vector<Port> ports;

    Node(int i, std::string t, Vec2 p) :id(i), title(t), pos(p) {}
    virtual ~Node() = default;

    virtual void update(GameState& gs, float dt) = 0;

    Vec2 portWorldPos(int i) const;
    bool hitBody(const Vec2& w) const;
    int hitPort(const Vec2& w) const;

    virtual void draw(GameState& gs) const;
};
