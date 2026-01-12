#include "graphics.h"
#include "app/App.h"
#include "core/Config.h"

static App g_app;

static void onUpdate(float ms) {
    g_app.update(ms / 1000.0f);
}

static void onDraw() {
    g_app.draw();
}

// Αυτό είναι που ζητάει το sggd.lib
int SDL_main(int argc, char** argv)
{
    (void)argc; (void)argv;

    graphics::createWindow(cfg::WINDOW_W, cfg::WINDOW_H, "Cloth Sim (SGG)");
    graphics::setCanvasSize((float)cfg::WINDOW_W, (float)cfg::WINDOW_H);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    g_app.init();

    graphics::setUpdateFunction(onUpdate);
    graphics::setDrawFunction(onDraw);
    graphics::startMessageLoop();
    return 0;
}

// Κρατάμε και κανονικό main για Console subsystem
int main(int argc, char** argv)
{
    return SDL_main(argc, argv);
}
