#pragma once

namespace input
{
    struct InputState
    {
        bool lmb_down = false;
        bool lmb_pressed = false;
        bool lmb_released = false;

        float mx = 0.0f;   // canvas coords
        float my = 0.0f;

        float pmx = 0.0f;  // previous
        float pmy = 0.0f;
    };
}
namespace input { void updateInput(InputState& in); }
