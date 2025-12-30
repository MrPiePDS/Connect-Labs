#include "NodeTypes.h"
#include "GameState.h"

static void IN(Node& n, ResourceType t, float y)
{
    Port p;
    p.name = "in";
    p.type = t;
    p.isOutput = false;

    // ΚΟΛΛΑΕΙ ΣΤΗΝ ΑΡΙΣΤΕΡΗ ΠΛΕΥΡΑ ΜΕΣΑ ΣΤΟ RECT
    p.localPos = { -n.w * 0.5f + 8.0f, y };
    n.ports.push_back(p);
}
static void OUT(Node& n, ResourceType t, float y)
{
    Port p;
    p.name = "out";
    p.type = t;
    p.isOutput = true;

    // ΚΟΛΛΑΕΙ ΣΤΗΝ ΔΕΞΙΑ ΠΛΕΥΡΑ ΜΕΣΑ ΣΤΟ RECT
    p.localPos = { n.w * 0.5f - 8.0f, y };
    n.ports.push_back(p);
}


NetworkNode::NetworkNode(int id, Vec2 p) : Node(id, "Network", p)
{
    h = 110.0f;
    OUT(*this, ResourceType::Text, 0.0f);
}
void NetworkNode::update(GameState&, float dt) {
    text += 8 * dt;
}

DownloaderNode::DownloaderNode(int id, Vec2 p) : Node(id, "Downloader", p)
{
    h = 120.0f;
    IN(*this, ResourceType::Text, -10.0f);
    OUT(*this, ResourceType::Text, 10.0f);
}

UploaderNode::UploaderNode(int id, Vec2 p) : Node(id, "Uploader", p)
{
    h = 120.0f;
    IN(*this, ResourceType::Text, -10.0f);
    OUT(*this, ResourceType::Money, 10.0f);
}
void UploaderNode::update(GameState&, float dt) {
    float c = std::min(text, 3 * dt);
    text -= c; money += c;
}

CollectorNode::CollectorNode(int id, Vec2 p) : Node(id, "Collector", p)
{
    h = 110.0f;
    IN(*this, ResourceType::Money, 0.0f);
}
void CollectorNode::update(GameState& gs, float dt) {
    float c = std::min(money, 10 * dt);
    money -= c; gs.bankMoney += c;
}
