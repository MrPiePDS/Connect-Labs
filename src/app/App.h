#pragma once

#include "cloth/ClothSim.h"
#include "input/InputState.h"

class App {
public:
    void init();
    void update(float dt);
    void draw();

private:
    ClothSim cloth;
    input::InputState m_input;
};
