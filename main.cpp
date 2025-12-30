#include <sgg/graphics.h>
#include "GameState.h"

static GameState gs;

void draw() { gs.draw(); }
void update(float dt) { gs.update(dt); }

int main() {
    graphics::createWindow(1280, 720, "Upload Labs");
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    gs.init();
    graphics::startMessageLoop();
    return 0;
}
