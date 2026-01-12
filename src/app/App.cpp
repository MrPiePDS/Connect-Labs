#include "app/App.h"
#include "core/Config.h"
#include "input/InputState.h"


void App::init() {
    cloth.init(cfg::CLOTH_COLS, cfg::CLOTH_ROWS, cfg::CLOTH_SPACING);

}

void App::update(float dt)
{
    input::updateInput(m_input);
    cloth.update(dt);

}

void App::draw() {
    cloth.draw();
}
