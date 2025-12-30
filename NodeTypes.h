#pragma once
#include "Node.h"

class NetworkNode : public Node {
public:
    NetworkNode(int id, Vec2 p);
    void update(GameState&, float dt) override;
};

class DownloaderNode : public Node {
public:
    DownloaderNode(int id, Vec2 p);
    void update(GameState&, float) override {}
};

class UploaderNode : public Node {
public:
    UploaderNode(int id, Vec2 p);
    void update(GameState&, float dt) override;
};

class CollectorNode : public Node {
public:
    CollectorNode(int id, Vec2 p);
    void update(GameState&, float dt) override;
};
